#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "bhv_kick_to_goal.h"
#include <rcsc/action/body_kick_one_step.h>
#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/common/player_param.h>
#include <rcsc/player/intercept_table.h>
#include <rcsc/geom/angle_deg.h>
#include <rcsc/player/player_agent.h>
using namespace rcsc;

bool Bhv_KickToGoal::execute( PlayerAgent * agent ){
    const WorldModel & wm = agent->world();
    if(wm.self().isKickable()){
        Vector2D face_point( ServerParam::i().theirTeamGoalPos().x,
                                ServerParam::i().theirTeamGoalPos().y );
        return Body_KickOneStep( face_point,
                          ServerParam::i().ballSpeedMax()
                          ).execute( agent );
                  
    }
    return false;
}