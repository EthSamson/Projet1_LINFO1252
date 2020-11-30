DIR1 = task1
DIR2 = task2
PY3 = python3

POSIX_PHILO_STATS = $(DIR1)/stats/philo.csv
POSIX_PRODCONS_STATS = $(DIR1)/stats/prodcons.csv
POSIX_READWRITE_STATS = $(DIR1)/stats/readwrite.csv

MY_PHILO_STATS = $(DIR2)/stats/philo.csv
MY_PRODCONS_STATS = $(DIR2)/stats/prodcons.csv
MY_READWRITE_STATS = $(DIR2)/stats/readwrite.csv
TAS_STAT = $(DIR2)/stats/tas.csv
TATAS_STAT = $(DIR2)/stats/tatas.csv

allGraph: Gphilo Gprodcons Greadwrite Gtastatas

allScript1:
	@(cd $(DIR1) && $(MAKE) -s all)

allScript2:
	@(cd $(DIR2) && $(MAKE) -s all)

Gphilo: graph_philo.py
ifeq (,$(wildcard $(POSIX_PHILO_STATS)))
	@echo "pas de stats pour philo posix.."
	@echo "lancement script philo posix.."
	@(cd $(DIR1) && $(MAKE) -s task1_1)
endif
ifeq (,$(wildcard $(MY_PHILO_STATS)))
	@echo "pas de stats pour philo my_mutex.."
	@echo "lancement script philo my_mutex.."
	@(cd $(DIR2) && $(MAKE) -s scriptPhilo)
endif
	@$(PY3) $<

Gprodcons: graph_prodcons.py
ifeq (,$(wildcard $(POSIX_PRODCONS_STATS)))
	@echo "pas de stats pour prodcons posix.."
	@echo "lancement script prodcons posix.."
	@(cd $(DIR1) && $(MAKE) -s task1_2)
endif
ifeq (,$(wildcard $(MY_PRODCONS_STATS)))
	@echo "pas de stats pour prodcons my_mutex.."
	@echo "lancement script prodcons my_mutex.."
	@(cd $(DIR2) && $(MAKE) -s scriptProdcons)
endif
	@$(PY3) $<

Greadwrite: graph_readwrite.py
ifeq (,$(wildcard $(POSIX_READWRITE_STATS)))
	@echo "pas de stats pour readwrite posix.."
	@echo "lancement script readwrite posix.."
	@(cd $(DIR1) && $(MAKE) -s task1_3)
endif
ifeq (,$(wildcard $(MY_READWRITE_STATS)))
	@echo "pas de stats pour readwrite my_mutex.."
	@echo "lancement script readwrite my_mutex.."
	@(cd $(DIR2) && $(MAKE) -s scriptReadwrite)
endif
	@$(PY3) $<

Gtastatas: graph_tas_tatas.py
ifeq (,$(wildcard $(TAS_STAT)))
	@echo "pas de stats pour test and set.."
	@echo "lancement script test and set.."
	@(cd $(DIR2) && $(MAKE) -s scriptTas)
endif
ifeq (,$(wildcard $(TATAS_STAT)))
	@echo "pas de stats pour test and test and set.."
	@echo "lancement script test and test and set.."
	@(cd $(DIR2) && $(MAKE) -s scriptTatas)
endif
	@$(PY3) $<

clean1:
	@(cd $(DIR1) && $(MAKE) -s clean)

clean2:
	@(cd $(DIR2) && $(MAKE) -s clean)

mrproper1: clean1
	@(cd $(DIR1) && $(MAKE) -s mrproper)

mrproper2: clean2
	@(cd $(DIR2) && $(MAKE) -s mrproper)