with Text_IO; use Text_IO;
procedure Main is
    task displayLetter1;
    task displayLetter2;
    task body displayLetter1 is
        begin
            loop
                Put_line("A");
                delay 1.0;
                Put_line("B");
                delay 1.0;
            end loop;
    end displayLetter1;
    task body displayLetter2 is
        begin
            loop
                Put_line("C");
                delay 1.0;
                Put_line("D");
                delay 1.0 ;
            end loop;
    end displayLetter2;
begin
    null;
end Main;