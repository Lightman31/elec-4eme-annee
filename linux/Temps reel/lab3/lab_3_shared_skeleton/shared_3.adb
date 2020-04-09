with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with System.Multiprocessors; use System.Multiprocessors;
with Resources; use Resources;

procedure Shared_3 is
   procedure Stack_Prefault;
   pragma Import (C, Stack_Prefault, "stack_prefault");
   procedure Lock_Memory;
   pragma Import (C, Lock_Memory, "lock_memory");  
   -- Import the C function "job" in jobs.c
   procedure Job(FET: Long_Integer);
   pragma Import (C, Job, "job");
   -- Declare a shared protected resource Shared_Data of type Resource ...
   Shared_Data : Resource(0);
   -- Declare an anonymous task High_Priority_Task, set its affinity and priority PH ...
   task High_Priority_Task with Priority => System.Priority'Last, CPU => 1;
   -- Declare an anonymous task Medium_Priority_Task, set its affinity and priority PM = PH - 1 ...   
   task Medium_Priority_Task with Priority => System.Priority'Last - 1, CPU => 1;
   -- Declare an anonymous task Low_Priority_Task, set its affinity and priority PL = PM - 1 ...
   task Low_Priority_Task with Priority => System.Priority'Last - 2, CPU => 1;
   
   -- High_Priority_Task is a periodic task of 4 iterations where: 
   -- * FET = 100ms;
   -- * relative deadline (implicit) = 200ms ...
   task body High_Priority_Task is 
      Next : Ada.Real_Time.Time;
      -- Set the period ...
      Period : constant Time_Span := Milliseconds(200);
      -- Set the deadline ...
      Deadline : constant Time_Span := Milliseconds(200);
      -- Set the FET ...
      FET_ns : constant Long_Integer := 100_000_000;
   begin 
      Next := Ada.Real_Time.Clock;     
      for J in 1 .. 4 loop
         begin 
            -- Launch the normal execution ...
              Job(FET_ns);
            -- Check if the deadline is respected ...
          	if (Ada.Real_Time.Clock - Next) > Deadline then
          		Put_Line("deadlines ratees High_Priority_Task");
            end if;
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
      Period : constant Time_Span := Milliseconds(400);
      -- Set the deadline ...
      Deadline : constant Time_Span := Milliseconds(400);
      -- The task job is split into equal parts of 50ms: 
      -- the first part is a normal execution,
      -- the second part is the critical section.
      -- Delays should be declared as long integers ...
      FET_ns : constant Long_Integer := 100_000_000;
      
   begin 
      Next := Ada.Real_Time.Clock;     
      for J in 1 .. 2 loop
         begin 
            -- Launch the normal execution ...
            Job(FET_ns/2);
            -- Launch the critical section ...
      			Shared_Data.Lock_For(FET_ns/2);
            -- Check if the deadline is respected ...
          	if (Ada.Real_Time.Clock - Next) > Deadline then
          		Put_Line("deadlines ratees Medium_Priority_Task");
            end if;
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
      Period : constant Time_Span := Milliseconds(800);
      -- Set the deadline ...
      Deadline : constant Time_Span := Milliseconds(800);
      -- The job is one critical section of 300ms ...
      FET_ns : constant Long_Integer := 300_000_000;
   begin  
      Next := Ada.Real_Time.Clock;
      for J in 1 .. 1 loop
         begin 
            -- Launch the critical section ...
            Shared_Data.Lock_For(FET_ns);
            Next := Next + Period;
            delay until Next;          
         end;
      end loop;
   end Low_Priority_Task;
begin  
   -- Lock the current and future memory allocations ...
   Lock_Memory;
   -- Pre-fault the stack ...
   Stack_Prefault;
end Shared_3;
