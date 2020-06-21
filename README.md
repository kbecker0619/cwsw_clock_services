# cwsw_clock_services

Components included in this package:
- Clock Services
- Alarms


tedlos notes/initialization/configuration
**remember**: a "table" in cwsw is a buffer with associated metadata.

list of OS events:      `eOsEvqEvents`. hard-coded, in file whose name is hard-coded to `tedlosevents.h`
    number of OS events:    `kNumOsEvqEvents`. hard-coded, must be last member of `eOsEvqEvents`

size of OS event queue: `kTedlos_EvQueueSize`. In project-specific config file.
event queue:
    event buffer:   `tblEventBuff`. hard-coded, private to tedlos
    event table:    `evTbl`, hard-coded, private to tedlos
event association:
    event-handler LUT:  `AssocArr`. hard-coded, private to tedlos. SIZE IS DERIVED FROM THE NUMBER OF EVENTS IN THE OS EVENT LIST
    event-handler association table: `tblEvH`. hard-coded, private to tedlos.

list of alarms managed by tedlos: file `ManagedAlarms.h` 
    TODO: change name to clearly associate it with tedlos

in tedlos, a "task" is basically an alarm; therefore, by providing a list of managed alarms, you're providing the list of tasks.

NOTE: the list of managed alarms is static, and handler by the tedlos scheduler.
    dynamic lists must be managed "by hand" within one (or more) of the managed tasks.

