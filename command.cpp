#include "command.h"
#include "vaisseau_data.h"
#include "option.h"

int mod (int a, int b)
{
   if(b < 0)
     return mod(a, -b);
   int ret = a % b;
   if(ret < 0)
     ret+=b;
   return ret;
}

void handle_command(struct command *cmd)
{
	struct vaisseau_data *vaisseau=cmd->controlled_ship;
	
    if (!vaisseau->explode) 
    {
        
        if (!(vaisseau->landed)||(vaisseau->rebound))
        {
            if (cmd->left)										 // Left arrow?
                vaisseau->angle-=vaisseau->anglestep; 								     // yes, on tourne a droite
            
            if (cmd->right) 									 // Right arrow?
                vaisseau->angle+= vaisseau->anglestep; 										   // yes, on tourne a gauche
            vaisseau->angle = mod(vaisseau->angle, 360);
          }
        
        if (cmd->shield)
        {
            vaisseau->shield = cmd->shield ;										   // shield activ
            
            if (vaisseau->shield && vaisseau->shield_force>0) 	// test shield si pas thrust
                vaisseau->sprite_buffer = vaisseau->gfx->sprite_shield; 			   // oui shield 
            else
                vaisseau->sprite_buffer = vaisseau->gfx->sprite;					   // non, normal
            
            vaisseau->thrust = (0);	  // pas de thrust

        }
        else
        {
            // thrust?
            if (vaisseau->fuel > 0 && cmd->thrust)
            {
                // pointe le sprite thrust
                if (vaisseau->option_type != OPT_THRUST) vaisseau->sprite_buffer = vaisseau->gfx->sprite_thrust; 
                else vaisseau->sprite_buffer = vaisseau->gfx->sprite_thrust2;
                vaisseau->thrust = vaisseau->thrust_max;						   // acceleration
                vaisseau->shield = false;								   // shield desactiv
                vaisseau->landed = false;										   // pas pos
            }
            else
            {
                vaisseau->thrust = (0);	  // pas de thrust
                vaisseau->sprite_buffer = vaisseau->gfx->sprite;					   // non, normal
                vaisseau->shield = false;								   // shield desactiv			
            }
        }
        
        if (cmd->fire && !vaisseau->fire && !vaisseau->shield)
            vaisseau->fire_delay=true;
        else
            vaisseau->fire_delay=false;
        
        if (cmd->fire && !vaisseau->shield)
            vaisseau->fire=true;
        else
            vaisseau->fire=false;
    }	
}
