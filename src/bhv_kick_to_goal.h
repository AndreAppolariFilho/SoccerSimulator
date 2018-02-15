#ifndef BHV_KICK_TO_GOAL_H
#define BHV_KICK_TO_GOAL_H

#include <rcsc/player/soccer_action.h>
#include <rcsc/geom/vector_2d.h>
class Bhv_KickToGoal:
    public rcsc::SoccerBehavior{
        public:
            Bhv_KickToGoal(){}
            bool execute( rcsc::PlayerAgent * agent );
    };
#endif