with Text_IO; use Text_IO;
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
    type taskA_ptr is access TaskA;
    t1: array(1 .. 2) of taskA_ptr;
    task body TaskB is
    Period : constant Time_Span := Milliseconds(1000);
    Next : Time := Clock;
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
    type taskB_ptr is access TaskB;
    t2: array(1 .. 2) of taskB_ptr;
begin
    for i in 1 .. 1 loop 
    t1(i):= new TaskA;
    t2(i):= new TaskB;
    end loop;
end Main;