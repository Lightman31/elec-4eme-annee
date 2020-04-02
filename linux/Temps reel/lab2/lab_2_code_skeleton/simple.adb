with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with System.Multiprocessors; use System.Multiprocessors;

procedure Simple is
   -- Import the C function stack_prefault defined in prefault.c ...
   procedure Stack_prefault;
   pragma Import  (C, Stack_prefault, "stack_prefault");
   -- Import the C function lock_memory defined in lock.c ...
   procedure Lock_memory;
   pragma Import (C, Lock_memory, "lock_memory");
   -- Import the C function job defined in jobs.c ...
   procedure Job(FET: Long_Integer);
   pragma Import (C, Job, "job");
   
   -- Define a task type RT_Task with the following parameters:
   -- * Id is the identifier,
   -- * FET is the fixed execution time in milliseconds (ms),
   -- * Prd is the Period in ms,
   -- * Itr is the number of iterations
   -- * Aff is the core affinity,
   -- * Pri is the priority. 
   task type RT_Task (Id, FET: Long_Integer; Prd, Itr: Integer; Aff: CPU; Pri: System.Priority) with CPU => Aff, Priority => Pri;
      
   -- RT_Task is a periodic task type with implicit deadlines ...
   task body RT_Task is 
      -- Set the period ...
      Period: constant Time_Span := Milliseconds(Prd);
      -- Set the deadline ...
      Deadline: constant Time_Span := Milliseconds(Prd);
      -- Set the FET in nanoseconds (ns): long integer to be passed to the imported function Job ...
      FET_ns: constant Long_Integer := FET * 1_000_000;
      -- Define the variable Next to save the next release instants of each job ...
      Next: Time;
   begin 
      -- Set the first release time in Next
   Next:= Clock;
      for J in 1 .. Itr loop
         begin
            -- Start the job ...
            Job(FET_ns);
            -- Check if the deadline is respected, print a message if not ...
            if Clock - Next > Deadline then
            	Put_Line(Id'Img & "deadlines ratees");
            end if;
            -- Set the next release time ...
            Next := Next + Period;
            -- Delay until Next ...
            delay until Next;
         end;
      end loop; 
   end RT_Task;
   
   -- Declare a named static task Tau_1 (type RT_Task, Id = 1): the parameters FET, Prd, Itr, Aff and Pri are to be adjusted according to the lab instructions ...
   Tau_1 : RT_Task(1,20,60,50,2,System.Priority'Last); 
   -- Declare a named static task Tau_2 (type RT_Task, Id = 2): the parameters FET, Prd, Itr, Aff and Pri are to be adjusted according to the lab instructions ...
   Tau_2 : RT_Task(2,40,60,50,2,System.Priority'Last); 
begin  
   -- Lock the current and future memory allocations ...
   Lock_memory;
   -- Pre-fault the stack ...
   Stack_prefault;
end Simple;
