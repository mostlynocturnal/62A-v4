#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"

void skills() {
    ///////////////////////////////////////////////
      //--------------FIRST SECTION----------------//
      ///////////////////////////////////////////////

      chassis.setPose(-60.451, 0, 90);

      //-----------ALLIANCE STAKE------------------//

      intakeInstance.move(0, 127);
      pros::delay(500);
      intakeInstance.stop();

      //-----------CLAMP FIRST MOGO------------------//

      chassis.moveToPoint(-48, 0, 850, {.forwards = true, .maxSpeed = 100});
      chassis.waitUntilDone();

      chassis.turnToPoint(-48, -24, 450);
      chassis.waitUntilDone();

      chassis.moveToPoint(-48, 24, 1000, {.forwards=false, .maxSpeed = 70});
      chassis.waitUntilDone();

      mogoInstance.clamp();

    //-----------SCORE ONE RING------------------//

      chassis.turnToPoint(-32, 24, 450);
      chassis.waitUntilDone();

      intakeInstance.move(127, 127);

      chassis.moveToPoint(-32, 24, 750, {.forwards=true, .maxSpeed = 100});
      chassis.waitUntilDone();


      //-----------OBTAIN 2nd RING------------------//

      //chassis.turnToPoint(24, 48, 500);
      //chassis.waitUntilDone();

      chassis.moveToPoint(24, 48, 1750, {.forwards=true, .maxSpeed = 100});
      pros::delay(1000);
      liftInstance.ready();
      chassis.waitUntilDone();

      chassis.moveToPoint(-13, 44, 1000, {.forwards=false, .maxSpeed = 100});
      chassis.waitUntilDone();
      liftInstance.wall();
      intakeInstance.move(127, -50);
      pros::delay(100);
      intakeInstance.move(127, 127);

      //-----------LADY BROWN 1------------------//

      chassis.turnToPoint(-11.5, 65, 500);
      chassis.waitUntilDone();

      chassis.moveToPose(-11.5, 65, 0, 1000, {.forwards=true, .maxSpeed =90});
      chassis.waitUntilDone();

      liftInstance.scorewall();
      pros::delay(450);

      //-----------SCORE THREE RINGS------------------//

      chassis.moveToPoint(-11.5, 40, 750, {.forwards=false, .maxSpeed = 100});
      chassis.waitUntilDone();
      liftInstance.stow();


      chassis.turnToPoint(-33, 40, 500);
      chassis.waitUntilDone();

      chassis.moveToPoint(-33, 40, 1000, {.forwards=true, .maxSpeed = 90});
      chassis.waitUntilDone();

      chassis.moveToPoint(-68, 40, 1750, {.forwards=true, .maxSpeed = 60});
      chassis.waitUntilDone();

     // chassis.turnToPoint(-49, 57, 500);
      //chassis.waitUntilDone();

      chassis.moveToPoint(-42, 55, 1000, {.forwards=true});
      chassis.waitUntilDone();

      //-----------Place in corner------------------//

      //chassis.turnToPoint(-59, 59, 500, {.forwards = false});
     // chassis.waitUntilDone();

      chassis.moveToPoint(-62, 62, 1000, {.forwards=false});
      chassis.waitUntilDone();

      mogoInstance.release();
      intakeInstance.stop();
}
