#pragma once
class Mission
{
	private:
		int formulation_day;
		char type;
		int target_location;
		int mission_duration;
		int significance;
		int id;
		int start_day;

	public:
		Mission();
		Mission(char input_mission_type, int input_formulation_day, int input_target_location, int input_mission_duration, int input_significance,int input_id);

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

		void set_id(int input_id);
		int get_id();

		void set_start_day(int start);
		int get_start_day();
	
};

