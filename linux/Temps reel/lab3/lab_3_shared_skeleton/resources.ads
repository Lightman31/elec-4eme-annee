package Resources is   
   -- Import the C function "job_with_cpu_time_returned" from jobs.c
   function Job_With_Cpu_Time_Returned (FET_ns : Long_Integer) return Long_Integer;
   pragma Import(C, Job_With_Cpu_Time_Returned, "job_with_cpu_time_returned"); 
   protected type Resource(Initial_Value : Long_Integer) is
      function Read return Long_Integer;
      procedure Write(New_Value : Long_Integer);
      procedure Lock_For(Lock_Time : Long_Integer);
   private
      The_Data : aliased Long_Integer := Initial_Value;  
   end Resource;
end Resources; 
