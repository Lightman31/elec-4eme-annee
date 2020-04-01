with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with System.Multiprocessors; use System.Multiprocessors;

procedure Simple is
   -- Import the C function stack_prefault defined in prefault.c ...
   pragma Import  (C, Stack_prefault, "stack_prefault");
   -- Import the C function lock_memory defined in lock.c ...
   pragma Import (C, Lock_memory, "lock_memory");
   -- Import the C function job defined in jobs.c ...
   pragma Import (C, Job, "job");
   
   -- Define a task type RT_Task with the following parameters:
   -- * Id is the identifier,
   -- * FET is the fixed execution time in milliseconds (ms),
   -- * Prd is the Period in ms,
   -- * Itr is the number of iterations
   -- * Aff is the core affinity,
   -- * Pri is the priority. 
   task type RT_Task is
  		entry Directory_Enquiry(Id : in identifier; FET : in exec_time; Prd: in Period; Itr: in iterations; Aff: in affinity; Pri: in priority);
   end RT_Task;
      
   -- RT_Task is a periodic task type with implicit deadlines ...
   task body RT_Task is 
      -- Set the period ...
      
      -- Set the deadline ...
      
      -- Set the FET in nanoseconds (ns): long integer to be passed to the imported function Job ...
      
      -- Define the variable Next to save the next release instants of each job ...
   begin 
      -- Set the first release time in Next
      accept Directory_Enquiry(Id : in identifier; FET : in exec_time; Prd: in Period; Itr: in iterations; Aff: in affinity; Pri: in priority) do
      for J in 1 .. Itr loop
         begin
            -- Start the job ...
            Job(FET);
            -- Check if the deadline is respected, print a message if not ...
            
            -- Set the next release time ...
            
            -- Delay until Next ...
            
         end;
      end loop; 
    end Directory_Enquiry;
   end RT_Task;
   
   -- Declare a named static task Tau_1 (type RT_Task, Id = 1): the parameters FET, Prd, Itr, Aff and Pri are to be adjusted according to the lab instructions ...
   --task type Tau_1; --pas fini
   -- Declare a named static task Tau_2 (type RT_Task, Id = 2): the parameters FET, Prd, Itr, Aff and Pri are to be adjusted according to the lab instructions ...
   --task type Tau_2; --pas fini
begin  
   -- Lock the current and future memory allocations ...
   
   -- Pre-fault the stack ...
   
end Simple;
