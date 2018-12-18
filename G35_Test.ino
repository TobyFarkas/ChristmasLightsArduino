/* -*- mode: c; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; -*-

   G35: An Arduino library for GE Color Effects G-35 holiday lights.
   Copyright © 2011 The G35 Authors. Use, modification, and distribution are
   subject to the BSD license as described in the accompanying LICENSE file.

By Mike Tsao <github.com/sowbug>. See README for complete attributions. */
 
// and Mark Ortiz
 
//Includes multiple button handling by ladyada: http://www.adafruit.com/blog/2009/10/20/example-code-for-multi-button-checker-with-debouncing/
 
#include <MEOG35String.h>
#include <MEOG35StringGroup.h>
#include <MEOProgramRunner.h>
#include <MEOPrograms.h>
  
//timer
#define PROG_DUR_LONG 86400  //24 hours
#define PROG_DUR_SHORT 120  //2 minutes
 
//Lights initialisation
MEOG35String lights(13, 50, 50, 0, false);
 
const int PROGRAM_COUNT = 600; //MEOProgramGroup::ProgramCount;
 
MEOProgramGroup programs;
MEOG35StringGroup string_group;
 
bool lightsOn = true;
bool firstTime = true;
 
MEOLightProgram* CreateProgram(uint8_t program_index, uint8_t pattern)
{
//  program_index = 15;
  Serial.print("Program count: ");
  Serial.println(PROGRAM_COUNT);
  Serial.print("Program index: ");
  Serial.println(program_index);
  Serial.print("Pattern index: ");
  Serial.println(pattern);
	return programs.CreateProgram(string_group, program_index, pattern);
}
 
uint16_t programDuration = PROG_DUR_SHORT; //set for short first, as random is first
 
MEOProgramRunner runner(CreateProgram, PROGRAM_COUNT, programDuration);
 
void setup()
{
  Serial.begin(9600);
	//Lights
	delay(10);
	 
	lights.enumerate();
	//lights_2.enumerate();
	 
	string_group.AddString(&lights);
	//string_group.AddString(&lights_2);
	 
	randomSeed(analogRead(0));
  Serial.println("setup complete");
}

void loop()
{
	if (firstTime)
	{
			//ensure not on Random (the other Ethernet Arduino could have put in any state)
			programDuration = PROG_DUR_SHORT;
			//runner.program_duration_seconds_ = 86400;
      runner.random_program();
//      Serial.print("Program index: ");
//      Serial.println(runner.program_index_);
//      Serial.println(runner.program_index_)
//			runner.initial_prog_patt(); //put to first program/pattern
//      runner.switch_program(true);
//      runner.switch_program(true);
//			runner.same_program();
			firstTime = false;
	} else {
		runner.loop();
	}
}
 

 
