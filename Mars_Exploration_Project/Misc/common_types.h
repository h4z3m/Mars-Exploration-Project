#pragma once
/*Unsigned numbers*/
typedef unsigned int   uint32;	/* 0              - 4,294,967,295  */
typedef unsigned short uint16;  /* 0              - 65,535		   */
typedef unsigned char  uint8;   /* 0              - 255			   */
/*Signed numbers*/
typedef signed int sint32;		/*-2,147,483,648  - +2,147,483,647 */
typedef signed int sint16;		/* -32,768        - +32,767	       */
typedef signed int sint8;		/*-128            - +127		   */

enum Rover_Types {
	EMERGENCY = 'E',
	POLAR = 'P',
	MOUNTAIN= 'M'
};