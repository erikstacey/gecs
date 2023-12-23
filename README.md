# General Entity Component System (GECS)

GECS is a lightweight C library which provides an optimized memory structure for applications which rely heavily on bulk processing of groups of similar data. The design philosophy of GECS focuses on
keeping the library lightweight and free of application-specific fluff, while remaining easy to use. Currently, this library is an early work-in-progress with its basic memory structures and management 
systems implemented, but it is currently lacking the bulk of what makes up an ECS. The current plan is to develop the entity and component management structures concurrently, then develop a systems
management structure which permits the user to provide instructions for operating on the component data.
