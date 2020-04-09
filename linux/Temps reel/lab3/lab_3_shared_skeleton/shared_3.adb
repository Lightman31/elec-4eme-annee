with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with System.Multiprocessors; use System.Multiprocessors;
with Resources; use Resources;

procedure Shared_3 is
   procedure Stack_Prefault;
   pragma Import (C, Stack_Prefault, "stack_prefault");
   procedure Lock_Mem;
   pragma Import (C, Lock_Mem, "lock_memory");  
   -- Import the C function "job" in jobs.c
   
   -- Declare a shared protected resource Shared_Data of type Resource ...
   
   -- Declare an anonymous task High_Priority_Task, set its affinity and priority PH ...
   
   -- Declare an anonymous task Medium_Priority_Task, set its affinity and priority PM = PH - 1 ...   
   
   -- Declare an anonymous task Low_Priority_Task, set its affinity and priority PL = PM - 1 ...
   
   
   -- High_Priority_Task is a periodic task of 4 iterations where: 
   -- * FET = 100ms;
   -- * relative deadline (implicit) = 200ms ...
   task body High_Priority_Task is 
      Next : Ada.Real_Time.Time;
      -- Set the period ...
      
      -- Set the deadline ...
      
      -- Set the FET ...

   begin 
      Next := Ada.Real_Time.Clock;     
      for J in 1 .. 4 loop
         begin 
            -- Launch the normal execution ...
              
            -- Check if the deadline is respected ...
          
            Next := Next + Period;
            delay until Next;           
         end;
      end loop; 
   end High_Priority_Task;
   
   
   -- Medium_Priority_Task is a periodic task of 2 iterations where: 
   -- * FET = 100ms;
   -- * relative deadline (implicit) = 400ms ...
   task body Medium_Priority_Task is 
      Next : Ada.Real_Time.Time;
      -- Set the period ...
      
      -- Set the deadline ...
      
      -- The task job is split into equal parts of 50ms: 
      -- the first part is a normal execution,
      -- the second part is the critical section.
      -- Delays should be declared as long integers ...
      
   begin 
      Next := Ada.Real_Time.Clock;     
      for J in 1 .. 2 loop
         begin 
            -- Launch the normal execution ...
            
            -- Launch the critical section ...
            
            -- Check if the deadline is respected ...
          
            Next := Next + Period;
            delay until Next;           
         end;
      end loop; 
   end Medium_Priority_Task;

   -- Low_Priority_Task is a periodic task of 1 iteration where 
   -- * FET = 300ms;
   -- * relative deadline (implicit) = 800ms ...
   task body Low_Priority_Task is  
      Next : Ada.Real_Time.Time;
      -- Set the period ...
      
      -- Set the deadline ...
      
      -- The job is one critical section of 300ms ...
      
   begin  
      Next := Ada.Real_Time.Clock;
      for J in 1 .. 1 loop
         begin 
            -- Launch the critical section ...
            
            Next := Next + Period;
            delay until Next;          
         end;
      end loop;
   end Low_Priority_Task;
begin  
   -- Lock the current and future memory allocations ...
   
   -- Pre-fault the stack ...
   
end Shared_3;
