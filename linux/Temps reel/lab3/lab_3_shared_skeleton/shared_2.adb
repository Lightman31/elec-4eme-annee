with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with System.Multiprocessors; use System.Multiprocessors;
with Resources; use Resources;

procedure Shared_2 is
   procedure Stack_Prefault;
   pragma Import (C, Stack_Prefault, "stack_prefault");
   procedure Lock_Memory;
   pragma Import (C, Lock_Mem, "lock_memory");
   -- Import the C function "job" in jobs.c
   procedure Job(FET: Long_Integer);
   pragma Import (C, Job, "job");
   
   -- Declare a shared protected resource Shared_Data of type Resource ...
   Shared_Data := Resources(0);
   -- Declare an anonymous task High_Priority_Task, set its affinity and priority PH ...
   task High_Priority_Task with Priority => System.Priority'Last, CPU => 1;
   -- Declare an anonymous task Low_Priority_Task, set its affinity and priority PL = PH - 1 ...
   task Low_Priority_Task with Priority => System.Priority'Last-1, CPU => 1;
   
   -- High_Priority_Task is a periodic task of 2 iterations where: 
   -- * FET = 200ms;
   -- * relative deadline (implicit) = 400ms ...
   task body High_Priority_Task is 
      Next : Ada.Real_Time.Time;
      -- Set the period ...
      Period : constant Time_Span := Milliseconds(200);
      -- Set the deadline ...
      Deadline : constant Time_Span := Milliseconds(400);
      -- The task jobs is split into equal parts of 100ms: 
      -- the first part is a normal execution,
      -- the second part is the critical section.
      -- Delays should be declared as long integers ...
      FET_ns : constant Long_Integer := 200_000_000;
   begin 
      Next := Ada.Real_Time.Clock;     
      for J in 1 .. 2 loop
         begin 
            -- Launch the normal execution ...
            Job(FET_ns/2)
            -- Launch the critical section ...
            Shared_Data.Lock_For(FET_ns/2);
            -- Check if the deadline is respected ...
          	if Ada.Real_Time.Clock - Next > Deadline then
          		Put_Line("deadlines ratees High_Priority_Task");
            end if;
            Next := Next + Period;
            delay until Next;           
         end;
      end loop; 
   end High_Priority_Task;
   
   
   -- Low_Priority_Task is a periodic task of 1 iteration where 
   -- * FET = 500ms;
   -- * relative deadline (implicit) = 800ms ...
   task body Low_Priority_Task is  
      Next : Ada.Real_Time.Time;
      -- Set the period ...
      Period : constant Time_Span := Milliseconds(500);
      -- Set the deadline ...
      Deadline : constant Time_Span := Milliseconds(800);
      -- The job is one critical section of 500ms ...
      FET_ns : constant Long_Integer := 500_000_000;
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
end Shared_2;
