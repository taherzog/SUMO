/*
 * HardFault.c
 *
 *  Created on: 09.10.2014
 *      Author: pherzog
 */



/*!
 * \brief This function should result in a HardFault
 *
 * Create a Hard-Fault for Debug-Reasons
 *
 * \param void

 */
void cause_hard_fault(void) {
  func(); /* will cause a hard fault, as the function pointer is NULL */
}
