; --------------------------------------------------------------------------------
; @Title: TRACE32 LiteOS RTOS Support - README
; @Description: -
; @Author: -
; @Copyright: (C) 1989-2022 Lauterbach GmbH, licensed for use with TRACE32(R) only
; --------------------------------------------------------------------------------
; $Id: readme.txt 18850 2022-01-26 18:41:29Z bschroefel $

---------------------------
Quick Configuration Guide:
---------------------------
To get a quick access to the features of the LiteOS RTOS debugger
with your application, follow this roadmap:
1. Start the TRACE32 Debugger.

2. Load your application as normal.

3. Execute the command: TASK.CONFIG liteos.t32

4. Execute the command: MENU.ReProgram liteos.men

5. Start your application.
Now you can access the LiteOS extensions through the menu.

-----------
Features :
-----------
The RTOS debugger for LiteOS supports the following features.

  * Display of Kernel Resources
  -----------------------------

The extension defines new PRACTICE commands to display various kernel resources.
   - TASK.Task : display tasks with detailed information including
   task id, name, state, priority, entry address. The "entry" field is mouse sensitive,
   double clicking on it opens appropriate windows.
   You can specify a Task magic or name to display detailed information 
   on that Task.
   
   - TASK.MUteX :  display a list of used mutexes.

   - TASK.SEMaphore : display a list of used semaphores.
   Without any arguments, a table with all used semaphores.
   You can specify a semaphore magic number to display detailed information 
   on that semaphore.

   - TASK.QUEue : display a list of used queues.
   Without any arguments, a table with all created message queues will be shown.
   You can specify a message queue magic number to display detailed information
   on that message
   queue.

   - TASK.TIMer : display a list of used timers.

The ’magic’ field in all LiteOS awareness windows is a unique ID, used by the 
RTOS Debugger to identify a specific (task, mutex, semaphore ..)..
The field ’magic’ is mouse sensitive, double clicking on it opens appropriate windows.
Right clicking on it will show a local menu.

If your hardware allows accessing the memory, while the target is running, 
these resources can be displayed  "On The Fly", i.e. while the application is running,
without any intrusion to the application. Without this capability, the information 
will only be displayed, if the target application is stopped.


  * Task Stack Coverage
  ---------------------
For stack usage coverage of the tasks, you can use the "TASK.STacK" command.
Without any parameter, this command will set up a window with all active tasks.
If you specify only a magic number as parameter, the stack area of this task 
will be automatically calculated. To use the calculation of the maximum stack 
usage, flag memory must be mapped to the task stack areas, when working with 
the emulation memory. When working with the target memory, a stack pattern 
must be defined with the command "TASK.STacK.PATtern" (default value is zero).

To add/remove one task to/from the task stack coverage, you can either call 
the "TASK.STacK.ADD" rsp."TASK.STacK.ReMove" commands with the task magic 
number as parameter, or omit the parameter and select from the task list window.

It is recommended, to display only the tasks, that you are interested in, 
because the evaluation of the used stack space is very time consuming and slows 
down the debugger display.


  * Task Related Breakpoints
  --------------------------
Any breakpoint set in the debugger can be restricted to fire only, if a specific 
task hits that breakpoint. This is especially useful, when debugging code which 
is shared between several tasks. To set a task related breakpoint, use the command:
"Break.Set <address>|<range> [/<option>] /TASK <task>" : Set task related breakpoint.

Use a task magic, ID or name for <task>.

By default, the task related breakpoint will be implemented by a conditional 
breakpoint inside the debugger. I.e., the target will always halt at that breakpoint, 
but the debugger immediately resumes execution, if the current running task is not 
equal to the specified task.

NOTE: Task related breakpoints impact the real-time behavior of the application.

For a general description of the  Break.Set command, please see its documentation.

When single stepping, the debugger halts on the next instruction, regardless which 
task hits this breakpoint. When debugging shared code, stepping over an OS function 
may lead to a task switch and coming back to the same place - but with a different task. 
If you want to "stick" the debugging within the current task you can set up the debugger 
with "SETUP.StepWithinTask ON" to use task related breakpoints for single stepping. 
In this case, single stepping will always stay within the current task. 
Other tasks using the same code will not be halted on these events.

If you want to halt program execution as soon as a specific task is scheduled to run 
by the OS, you can use the  Break.SetTask command.
by the OS, you can use the  Break.SetTask command.

  * Task Context Display
  ----------------------
You are able to switch the whole viewing context to a currently not executing task. 
This means, that all register and stack related information (such as Register, Data.List, Frame etc.) 
will be shown according to this task. Be aware that this is only for displaying information. 
When continuing debugging the application ( Step or  Go), the debugger will switch 
back to the current context.

For displaying a specific task context, use the command:
"Frame.TASK [<task>]" : Display task context.
Specify a task magic or a task name (in double quotes) as parameter.

To switch back to the current context, omit all parameters.

For displaying the call stack of a specific task, you can use the following command:
"Frame /Task <task>" : Display call stack of a task.

If you’d like to see the application code, where the task was preempted, execute the command
Frame /Caller /Task <task> to open a window of the same name. 
Double click on the line showing the OS service call.

  * Dynamic Task Performance Measurement
  --------------------------------------
The debugger may execute a dynamic performance measurement by evaluating the current 
running task in changing time intervals. Start the measurement with the commands  
"PERF.Mode TASK" and "PERF.Arm", and view the contents with "PERF.ListTASK". 
The evaluation is done by reading the ‘magic’ location (= current running task) in memory. 
This memory read may be non-intrusive or intrusive, depending on the "PERF.METHOD" used.

If "PERF" collects the PC for function profiling of processes in MMU based operating systems
("SYStem.Option MMUSPACES ON"), then you need to set "PERF.MMUSPACES", too.
For a general description of the  PERF command, refer to 
"General Commands Reference Guide P"  (general_ref_p.pdf).


  * Task Runtime Statistics
  -------------------------
NOTE:	This feature is only available, if your debugger equipment is able to trace 
task switches (see below).

Out of the recordings done by the  Trace (if available), the debugger is able to evaluate
the time spent in a task and display it statistically and graphically. 
To do this, the debugger must be able to detect the task switches out of the trace, 
i.e. the task switches need to be recorded.

Usually, there’s a variable in the system that holds the current running task. 
By recording the accesses to this memory location (aka "magic" location), the debugger 
detects a task switch by a change of this variable.
Please note, that the debugger equipment must be able to trace memory data accesses
in this case, program flow trace is not sufficient.

To do a selective recording on task switches with state analyzers (ICE and FIRE),
use the following PRACTICE commands:

   ---------------------------------------------------------------------------
  | ; Mark the magic location with an Alpha breakpoint                        |
  | Break.Set TASK.CONFIG(magic)++(TASK.CONFIG(magicsize)-1) /Alpha           |
  | ; Program the Analyzer to record only task switches                       |
  | Analyzer.ReProgram                                                        |
  | (                                                                         |
  | Sample.Enable if AlphaBreak&&Write                                        |
  | )                                                                         |
   ---------------------------------------------------------------------------

To do a selective recording on task switches with flow traces (ICD, e.g. ETM and NEXUS trace),
based on the data accesses, use the following PRACTICE command:

   -----------------------------------------------
  |  ; Enable tracing only on the magic location  |
  |  Break.Set TASK.CONFIG(magic) /TraceEnable    |
   -----------------------------------------------

To evaluate the contents of the trace buffer, use these commands:
 - Trace.List List.TASK DEFault : Display trace buffer and task switches
 - Trace.STATistic.TASK : Display task runtime statistic evaluation
 - Trace.Chart.TASK : Display task runtime timechart
 - Trace.PROfileSTATistic.TASK : Display task runtime within fixed time intervals statistically
 - Trace.PROfileChart.TASK : Display task runtime within fixed time intervals as colored graph
 - Trace.FindAll Address task.config(magic) : Display all data access records to the "magic" location
 - Trace.FindAll CYcle owner OR CYcle context : Display all context ID records

The start of the recording time, when the calculation doesn’t know, which task is running,
is calculated as "(unknown)".

  * Task State Analysis
  ---------------------
NOTE:	This feature is only available, if your debugger equipment is able to trace
memory data accesses (program flow trace is not sufficient).

The time different tasks are in a certain state (running, ready, suspended or waiting) 
can be evaluated statistically or displayed graphically.

This feature needs recording of all accesses to the status words of all tasks. 
Additionally, the accesses to the current task pointer (=magic) are needed. Adjust your 
trace logic to record all data write accesses, or limit the recorded data to the area 
where all TCBs are located (plus the current task pointer).

To do a selective recording on task states with state analyzers (ICE or FIRE), use
"TASK.TASKState", if available, to mark the status words with Alpha breakpoints.
Run the following PRACTICE script:

   ------------------------------------------------------------------------------
  | ; Mark the magic location with an Alpha breakpoint                           |
  | Break.Set task.config(magic)++(task.config(magicsize)-1) /Alpha              |
  | ; Mark all task state words with Alpha breakpoints                           |
  | TASK.TASKState                                                               |
  | ; Program the Analyzer to record task state transitions                      |
  |  Analyzer.ReProgram                                                          |
  | (                                                                            |
  |  Sample.Enable if AlphaBreak&&Write                                          |
  | )                                                                            |
   ------------------------------------------------------------------------------
 
To do a selective recording on task states with flow traces (ICD, e.g. ETM and NEXUS trace),
just enable the recording of all data write cycles.

To evaluate the contents of the trace buffer, use these commands:
 - Trace.STATistic.TASKState : Display task state statistic
 - Trace.Chart.TASKState : Display task state timechart

The start of the recording time, when the calculation doesn’t know, which task is running,
is calculated as "(unknown)".
All kernel activities up to the task switch are added to the calling task.


  * Function Runtime Statistics
  -----------------------------
NOTE:	This feature is only available, if your debugger equipment is able to trace memory data
accesses (program flow trace is not sufficient).

All function related statistic and timechart evaluations can be used with task specific information.
The function timings will be calculated dependent on the task, that called this function.
To do this, additionally to the function entries and exits, the task switches must be recorded.
To do a selective recording on task related function runtimes with state analyzers (ICE and FIRE),
use the following PRACTICE commands:

   ----------------------------------------------------------------------------
  | ; Mark the magic location with an Alpha breakpoint                         |
  | Break.Set TASK.CONFIG(magic)++(TASK.CONFIG(magicsize)-1) /Alpha            |
  | ; Mark the function entries/exits with Alpha/Beta breakpoints              |
  | Break.SetFunc                                                              |
  | ; Program the Analyzer to record function entries/exits and task switches  |
  | Analyzer.ReProgram                                                         |
  | (                                                                          |
  | Sample.Enable       if AlphaBreak||BetaBreak                               |
  | Mark.A              if AlphaBreak                                          |
  | Mark.B              if BetaBreak                                           |
  | )                                                                          |
   ----------------------------------------------------------------------------

To do a selective recording on task related function runtimes with flow traces
(ICD, e.g. ETM and NEXUS trace), based on the data accesses, use the following PRACTICE command:

   ----------------------------------------------------------------
  | ; Enable flow trace an accesses to the magic location          |
  | Break.Set TASK.CONFIG(magic) /TraceData                        |
   ----------------------------------------------------------------

To evaluate the contents of the trace buffer, use these commands:
 - Trace.ListNesting : Display function nesting
 - Trace.STATistic.Func : Display function runtime statistic
 - Trace.STATistic.TREE : Display functions as call tree
 - Trace.STATistic.sYmbol /SplitTASK : Display flat runtime analysis
 - Trace.Chart.Func : Display function timechart
 - Trace.Chart.sYmbol /SplitTASK : Display flat runtime timechart

The start of the recording time, when the calculation doesn’t know, which task is running,
is calculated as "(unknown)".


----------------------------
LiteOS PRACTICE Functions :
----------------------------
There are special definitions for LiteOS specific PRACTICE functions:

TASK.CONFIG(magic) : Returns the address of the magic number
TASK.CONFIG(magicsize) :Returns the size of the magic number

