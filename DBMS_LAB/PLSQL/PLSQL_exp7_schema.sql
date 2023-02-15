--create a table employee with fields empid,empname,joining_date,relieving_date,salary and insert values into it


DECLARE
	empid NUMBER;
	empname VARCHAR2(20);
	joining_date DATE;
	relieving_date DATE;
    salary NUMBER;
BEGIN	
	--create TABLE
	
	EXECUTE IMMEDIATE 'CREATE TABLE employee(empid NUMBER,empname VARCHAR2(50),joining_date DATE,relieving_date DATE,salary NUMBER)';
	
	--insert data into table
	
	empid:= 517314;
	empname:='James';
	joining_date:= to_date('2003-02-22', 'YYYY-MM-DD');
	relieving_date:= to_date('2023-02-22', 'YYYY-MM-DD');
	salary:=10000;
	EXECUTE IMMEDIATE 'INSERT INTO employee(empid,empname,joining_date,relieving_date,salary) VALUES (:v1,:v2,:v3,:v4,:v5)' USING empid,empname,joining_date,relieving_date,salary;
		
	empid:= 517314;
	empname:='Anson';
	joining_date:= to_date('2010-07-22', 'YYYY-MM-DD');
	relieving_date:= to_date('2022-04-25', 'YYYY-MM-DD');
	salary:=10000;
	EXECUTE IMMEDIATE 'INSERT INTO employee(empid,empname,joining_date,relieving_date,salary) VALUES (:v1,:v2,:v3,:v4,:v5)' USING empid,empname,joining_date,relieving_date,salary;
	
	empid:= 517314;
	empname:='Babu';
	joining_date:= to_date('2015-04-12', 'YYYY-MM-DD');
	relieving_date:= to_date('2021-04-25', 'YYYY-MM-DD');
	salary:=17000;
	EXECUTE IMMEDIATE 'INSERT INTO employee(empid,empname,joining_date,relieving_date,salary) VALUES (:v1,:v2,:v3,:v4,:v5)' USING empid,empname,joining_date,relieving_date,salary;
	
	empid:= 517314;
	empname:='Suraj';
	joining_date:= to_date('2014-01-15', 'YYYY-MM-DD');
	relieving_date:= to_date('2023-04-15', 'YYYY-MM-DD');
	salary:=15000;
	EXECUTE IMMEDIATE 'INSERT INTO employee(empid,empname,joining_date,relieving_date,salary) VALUES (:v1,:v2,:v3,:v4,:v5)' USING empid,empname,joining_date,relieving_date,salary;
	
	COMMIT;
	DBMS_OUTPUT.PUT_LINE('Table created and values inserted');
END;
/