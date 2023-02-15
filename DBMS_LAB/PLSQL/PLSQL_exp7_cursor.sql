--creating cursor to find service(in years) and pension of each employee

DECLARE 
	CURSOR c_employee IS
		SELECT empid,empname,joining_date,relieving_date,salary
		FROM employee;
	a_employee c_employee%ROWTYPE;
	SERVICE NUMBER;
	pension DECIMAL;
BEGIN	
	DBMS_OUTPUT.PUT_LINE('empid          empname        joining_date          relieving_date         salary        service(in years)		pension');
	DBMS_OUTPUT.PUT_LINE('-------------------------------------------------------------------------------------------------------------------------');
	OPEN c_employee;
	LOOP
		FETCH c_employee INTO a_employee;
		EXIT WHEN c_employee%NOTFOUND;
		SERVICE:=trunc(months_between(a_employee.relieving_date,a_employee.joining_date)/12);
		pension:=(SERVICE*a_employee.salary)/100;
		DBMS_OUTPUT.PUT_LINE(a_employee.empid||'          '||a_employee.empname||'        '||a_employee.joining_date||'          '||a_employee.relieving_date||'          '||a_employee.salary||'        '||SERVICE||'		'||pension);
	END LOOP;
	CLOSE c_employee;
END;
/