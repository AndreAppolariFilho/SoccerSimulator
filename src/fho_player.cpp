//Classes que eu possa utilizar
//Body_GoToPoint2010 ou Body_GoToPointDodge
//Body_TurnToBall

#include "fho_player.h"
#include "bhv_custom_before_kick_off.h"
#include "view_tactical.h"

#include <rcsc/action/body_go_to_point_dodge.h>
#include <rcsc/action/body_turn_to_ball.h>
#include <rcsc/action/body_advance_ball2009.h>

#include <rcsc/player/world_model.h>
void FhoPlayer::actionImpl(){
    const WorldMode & wm = this->world();
    if ( wm.gameMode().type() == GameMode::BeforeKickOff
         || wm.gameMode().type() == GameMode::AfterGoal_ ){
        dlog.addText( Logger::TEAM,
                      __FILE__": before_kick_off" );
        Vector2D move_point =  Strategy::i().getPosition( wm.self().unum() );
        Bhv_CustomBeforeKickOff( move_point ).execute( this );
        this->setViewAction( new View_Tactical() );
        return;
    }
    if(Body_AdvanceBall2009().execute( agent )) return;
if(!Body_GoToPointDodge(wm.ball().pos(),mytype.staminaIncMax() * wm.self().recovery()).execute(this)){
        Body_TurnToBall().execute(this);
    }
}
