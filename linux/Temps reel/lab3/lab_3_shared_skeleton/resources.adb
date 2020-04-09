package body Resources is
   protected body Resource is
      function Read return Long_Integer is
      begin
         -- Return the resource data ...
         return The_Data;
      end Read;
      procedure Write(New_Value : Long_Integer) is
      begin
         -- Write the new value in the resource ...
         The_Data := New_Value;
      end Write;
      procedure Lock_For(Lock_Time : Long_Integer) is 
      begin
         -- Lock the resource for a duration Lock_Time ...
         -- Indication: use the functions Write and job_with_cpu_time_returned ...
         Write(Job_With_Cpu_Time_Returned(Lock_Time));
      end Lock;      
   end Resource;
end Resources;
