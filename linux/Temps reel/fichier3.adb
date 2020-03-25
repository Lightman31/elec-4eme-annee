with Ada.Real_Time; use Ada.Real_Time;
procedure Main is
    task type TaskA;
    task type TaskB;
    task body TaskA is
    Period : constant Time_Span := Milliseconds(1000);
    Next : Time := Clock;
        begin
            loop
                Put_line("A");
                Next := Next + Period;
                delay until Next;
                Put_line("B");
                Next := Next + Period;
                delay until Next;
            end loop;
    end TaskA;
    task body TaskB is
        begin
            loop
                Put_line("C");
                Next := Next + Period;
                delay until Next;
                Put_line("D");
                Next := Next + Period;
                delay until Next;
            end loop;
    end TaskB;
begin
    null;
end Main;