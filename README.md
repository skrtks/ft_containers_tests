### Tests for ft_containers
###### _By Sam Kortekaas (skorteka)_

###### _Powered by Catch2_


##### Project structure:

In Makefile, include the directories that contain the includes you need for you containers to work. 

For the example file structure below you have to change INCLUDE in the ft_containers_tests Makefile to:

_INCLUDE = -I../List -I../Vector -I../Vector/Whatever_

    ft_containers/
    │
    └── List/
    │   └── List.hpp
    │
    └── Vector/
    │   ├── Vector.hpp
    │   │   ...
    │   │   ...
    │   └── Whatever/
    │       ├── Extra.hpp
    │       └── Utils.hpp
    │
    └── ft_containers_tests/

##### Usage:
- cd to ft_containers/ft_containers_tests/

Normal test run:
- make && ./ft_containers_tests

To run a subset of test, first make and then run with the tag of the subset you 
want to run. It is possible to run multiple subsets by adding more tags separated
 by a ',':
- make && ./ft_containers_tests "[List]", "[Map]"

You can also run a specific test by adding the name of the test as an argument:
- make && ./ft_containers_tests "Map: Constructors"

To stop testing on the first error / n errors:
- make && ./ft_containers_tests -a / -x n

For a more compact output run with -r compact. To get insights in memory problems 
please compile with "make asan=1"

