/** @file gameboard.cpp
  * @brief This file contains code for implementing the gameboard class

  * For now, code is mainly placeholder. I was unable to figure out how to create a viable gameboard class
  * that would create the GUI I envisioned of two boards and corresponding QCheckbox and QPushButton. Thus,
  * current GUI has been created through the ui. File will be expanded with implementation of gameboard GUI and logic
*/

#include "gameboard.h"

/**
 * @brief gameboard::gameboard
 * Default constructor does not do anything currently. Functionality will be expanded later
 */
gameboard::gameboard()
{

}

/**
 * @brief gameboard::~gameboard
 * Basic destructor. No calls to new made in my code
 */
gameboard::~gameboard(){
    delete ui;
}
