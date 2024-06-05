import yaml, sys
from yaml import CLoader as Loader

file = open(sys.argv[1], 'r')
doc = yaml.load_all(file, Loader=Loader)
enabledSkills = []
for data in doc:
	if (data['enabled']):
		enabledSkills.append(data)

if len(enabledSkills) > 254:
	print("ERROR: Too many skills enabled")
	print("The maximum is 254, and you enabled", len(enabledSkills))
else:
	print(len(enabledSkills), "skills enabled")


