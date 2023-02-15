declare 
	a number :=&a;
	i number (1);
	result integer :=0;
begin 
	for i in 1..a-1 loop
		if mod(a,i)=0 then
			result:=result+i;
		end if;
	end loop;
	if result=a then
		dbms_output.put_line(a||' is Perfect');
	else
		dbms_output.put_line(a|| ' is not Perfect');
	end if;
end;
/		