#pragma once
class Mission
{
	private:
		int formulation_day;
		char type;
		int target_location;
		int mission_duration;
		int significance;
	public:
		Mission();
		Mission(char input_mission_type, int input_formulation_day, int input_target_location, int input_mission_duration, int input_significance);

		void set_formulation_day(int input_formulation_day);
		int get_formulation_day();

		void set_mission_type(char input_mission_type);
		char get_mission_type();

		void set_target_location( int input_target_location);
		int get_target_location();

		void set_mission_duration(int input_mission_duration);
		int get_mission_duration();

		void set_significance(int input_significance);
		int get_significance();
	
};

