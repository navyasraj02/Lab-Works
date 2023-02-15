/*The following table shows the salary information of employees in a company. EMPLOYEE
(empid, empname, salary) Write a trigger that causes insertion of a new entry into the table
INCREMENT(empid, incr), if the difference arising due to an updation of the salary of an
existing employee is greater than Rs. 1000/-*/


--creating tables employee and increments

CREATE TABLE EMPLOYEE(empid INT PRIMARY KEY,
						empname VARCHAR(30),
						salary int);
INSERT INTO employee VALUES(71512,'Joseph',75000);
INSERT INTO employee VALUES(62112,'George',56000);
INSERT INTO employee VALUES(51912,'Malavika',33000);
INSERT INTO employee VALUES(81512,'Ramesh',80000);

CREATE TABLE Increments (
  empid int,
  incr int,
  PRIMARY KEY (empid, incr),
  FOREIGN KEY(empid) references Employee(empid) 
);
--creating trigger 

CREATE OR REPLACE TRIGGER salary_increment
AFTER UPDATE OF salary ON employee
FOR EACH ROW
DECLARE
  diff NUMBER;
BEGIN
  diff := :NEW.salary - :OLD.salary;
  IF diff > 1000 THEN
    INSERT INTO Increments (empid, incr)
    VALUES (:NEW.empid, diff);
  END IF;
END;
/

--updating salary of an employee

update employee
set salary = 58000
where empid=62112;

select * from increments;

