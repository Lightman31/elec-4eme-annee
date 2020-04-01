with Text_IO; use Text_IO;
with Ada.Calendar; use Ada.Calendar;
procedure Main is
    task type TaskA;
    task type TaskB;
    task body TaskA is
        begin
            loop
                Put_line("A");
                delay 1.0;
                Put_line("B");
                delay 1.0;
            end loop;
    end TaskA;
    type taskA_ptr is access TaskA;
    t1: array(1 .. 2) of taskA_ptr;
    task body TaskB is
        begin
            loop
                Put_line("C");
                delay 1.0;
                Put_line("D");
                delay 1.0;
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