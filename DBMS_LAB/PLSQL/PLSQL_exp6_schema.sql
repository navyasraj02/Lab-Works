--Given the scheme Person (pid, pname, DOB) . Find the age of each person using cursor

DECLARE	
	pid NUMBER;
	pname VARCHAR2(50);
	DOB DATE;
	
BEGIN
	--create table 
	
	EXECUTE IMMEDIATE 'CREATE TABLE Person(pid NUMBER,pname VARCHAR2(50),DOB DATE)';
	
	--insert data into table
	pid := 2378;
	pname := 'Silpa';
	DOB := to_date('2003-02-22', 'YYYY-MM-DD');
	EXECUTE IMMEDIATE 'INSERT INTO Person (pid,pname,DOB) VALUES (:v1,:v2,:v3)' USING pid,pname,DOB;
	
    pid := 6423;
	pname := 'priya';
	DOB := to_date('2005-05-26', 'YYYY-MM-DD');
	EXECUTE IMMEDIATE 'INSERT INTO Person (pid,pname,DOB) VALUES (:v1,:v2,:v3)' USING pid,pname,DOB;
	
	pid := 8192;
	pname := 'milan';
	DOB := to_date('2007-07-18', 'YYYY-MM-DD');
	EXECUTE IMMEDIATE 'INSERT INTO Person (pid,pname,DOB) VALUES (:v1,:v2,:v3)' USING pid,pname,DOB;
	--commit
	COMMIT;
	DBMS_OUTPUT.PUT_LINE('Table created and data inserted');
END;
/
