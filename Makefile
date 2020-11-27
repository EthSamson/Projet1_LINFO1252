DIR1 = task1
DIR2 = task2

all1:
	cd $(DIR1) && $(MAKE) all

#all2:
	#cd $(DIR2) && $(MAKE) all

clean:
	cd $(DIR1) && $(MAKE) $@
	cd $(DIR2) && $(MAKE) $@

mrproper:
	cd $(DIR1) && $(MAKE) $@
	#cd $(DIR2) && $(MAKE) $@
