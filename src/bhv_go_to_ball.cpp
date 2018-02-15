#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "bhv_go_to_ball.h"
#include "bhv_set_play.h"
#include "strategy.h"

#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_turn_to_ball.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>

#include <rcsc/geom/angle_deg.h>

#include <rcsc/player/player_agent.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>

using namespace rcsc;

bool Bhv_GoToBall::execute( PlayerAgent * agent ){
    const double angleTheta = 15.0;
    const WorldModel & wm = agent->world();
    Vector2D sub_target;
    double mag = 2.0;
    if(wm.ball().pos().y < wm.self().pos().y){
        sub_target = wm.ball().pos() -  Vector2D::polar2vector(mag,wm.ball().angleFromSelf() + 135.0);
    }else{
        sub_target = wm.ball().pos() +  Vector2D::polar2vector(mag,wm.ball().angleFromSelf() + 135.0);
    }
    if(wm.self().pos().x> sub_target.x ){
        Body_GoToPoint(sub_target,
        1,
        Strategy::i().get_normal_dash_power(wm)
        ).execute(agent);
        agent->setNeckAction(new Neck_TurnToBallOrScan());
        return true;
    }else{
        double dash_power = 20.0;
        double dash_speed = -1;
        
        if ( wm.ball().distFromSelf() > 2.0 ){
            dash_power = Bhv_SetPlay::get_set_play_dash_power( agent );
            
        }
        else{
            dash_speed = wm.self().playerType().playerSize();
            dash_power = wm.self().playerType().getDashPowerToKeepSpeed( dash_speed, wm.self().effort() );
        }
        if ( ( wm.ball().angleFromSelf() - wm.self().body() ).abs() > 1.5 )
            {
                dlog.addText( Logger::TEAM,
                                    __FILE__": turn to ball" );
                Body_TurnToBall().execute( agent );
                return true;
            }
            // dash to ball
            else
            {
                dlog.addText( Logger::TEAM,
                                    __FILE__": dash to ball" );
                agent->doDash( dash_power );
                return true;
            }
        
            agent->setNeckAction(new Neck_TurnToBallOrScan());
    }
    return false;
}
