with Text_IO; use Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
procedure Main is
    task type TaskA;
    task body TaskA is
        begin
            loop
                Put_line("Tick :");
                Put_line(Tick);
                delay 1.0;
            end loop;
    end TaskA;
begin
    null;
end Main;