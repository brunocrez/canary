-- Minlevel and multiplier are MANDATORY
-- Maxlevel is OPTIONAL, but is considered infinite by default
-- Create a stage with minlevel 1 and no maxlevel to disable stages
experienceStages = {
	{
		minlevel = 1,
		maxlevel = 1000,
		multiplier = 250,
	},
	{
		minlevel = 1001,
		maxlevel = 1500,
		multiplier = 200,
	},
	{
		minlevel = 1501,
		maxlevel = 2000,
		multiplier = 150,
	},
	{
		minlevel = 2001,
		maxlevel = 2500,
		multiplier = 100,
	},
	{
		minlevel = 2501,
		maxlevel = 3000,
		multiplier = 75,
	},
	{
		minlevel = 3001,
		maxlevel = 3500,
		multiplier = 50,
	},
	{
		minlevel = 3501,
		maxlevel = 4000,
		multiplier = 25,
	},
	{
		minlevel = 4001,
		maxlevel = 4500,
		multiplier = 12.5,
	},
	{
		minlevel = 4501,
		multiplier = 5,
	},
}

skillsStages = {
	{
		minlevel = 10,
		maxlevel = 39,
		multiplier = 20,
	},
	{
		minlevel = 40,
		maxlevel = 69,
		multiplier = 15,
	},
	{
		minlevel = 70,
		maxlevel = 99,
		multiplier = 10,
	},
	{
		minlevel = 100,
		multiplier = 5,
	},
}

magicLevelStages = {
	{
		minlevel = 0,
		maxlevel = 39,
		multiplier = 20,
	},
	{
		minlevel = 40,
		maxlevel = 69,
		multiplier = 15,
	},
	{
		minlevel = 70,
		maxlevel = 99,
		multiplier = 10,
	},
	{
		minlevel = 100,
		multiplier = 5,
	},
}
