declare
	a number :=&a;
	i number (1);
	flag number :=0;
begin
	if a=2 then
		dbms_output.put_line(a||' is prime');
	elsif a=3 then
		dbms_output.put_line(a||' is prime');
	else
		for i in 2..(a/2) loop
			if mod(a,i)=0 then
				dbms_output.put_line(a || ' is not prime');
				flag:=1;
				exit;
			end if;
		end loop;
		if flag=0 then 
			dbms_output.put_line(a|| ' is prime');
		end if;
	end if;
end;
/		