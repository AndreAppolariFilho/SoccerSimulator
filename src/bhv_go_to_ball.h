#ifndef AGENT2D_BHV_GO_TO_BALL_H
#define AGENT2D_BHV_GO_TO_BALL_H

#include <rcsc/player/soccer_action.h>
#include <rcsc/geom/vector_2d.h>
class Bhv_GoToBall:
    public rcsc::SoccerBehavior{
        public:
            Bhv_GoToBall(){}
            bool execute( rcsc::PlayerAgent * agent );
    };
#endif
