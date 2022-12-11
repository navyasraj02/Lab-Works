/*AUTHOR - NAVYA.S.RAJ
BATCH - S5 CSE
ROLL NO. - 51
SUBJECT - DBMS LAB*/

/*CREATING THE DATABASE*/
create database expt7;
use expt7;

/*CREATING THE TABLES*/
create table student(
stud_id int PRIMARY KEY,
stud_name varchar(20),
roll_no int(2),
utyreg_no varchar(10) ,
stud_address varchar(50),
passout_yr int,
admn_yr int,
branch varchar(5),
cls_adv varchar(15)
);

create table student_emailId(
stud_id int,
stud_emailId varchar(30),
FOREIGN KEY(stud_id) references student(stud_id)  ON DELETE CASCADE,
PRIMARY KEY(stud_id,stud_emailId)
);

create table student_phoneNo(
stud_id int,
phoneNo int,
FOREIGN KEY(stud_id) references student(stud_id)  ON DELETE CASCADE,
PRIMARY KEY(stud_id,phoneNo)
);

create table faculty(
fac_id int PRIMARY KEY,
fac_name varchar(20),
designation varchar(30),
join_date date,
relieved_date date
);

create table faculty_emailId(
fac_id int,
fac_emailId varchar(30),
PRIMARY KEY(fac_id,fac_emailId),
FOREIGN KEY(fac_id) references faculty(fac_id) ON DELETE CASCADE
);

create table qualification(
stud_id int,
total int,
grade char(20),
FOREIGN KEY(stud_id) references student(stud_id),
PRIMARY KEY(stud_id,total)
);

create table project(
stud_id int,
title varchar(20),
guide int,
core_area varchar(10),
prd_of_impl int,
FOREIGN KEY(stud_id) references student(stud_id)  ON DELETE CASCADE,
PRIMARY KEY(stud_id,title)
);

/*POPULATING THE DATABASE*/
INSERT INTO student VALUES(100,"ALLEN THOMAS",1,"KTE20CS01","24 STRETFORDEND",2024,2020,"CSE","VIPIN VASU"),
(101,"SANDRA SABU",2,"KTE20CS02","54 STRETFORDEND MANCHESTER",2024,2020,"CSE","VIPIN VASU"),
(102,"MUKIL M P",3,"KTE20CS03","65 STRETFORDEND MANCHESTER",2022,2018,"CSE","VIPIN VASU"),
(201,"NAVEENA",1,"KTE20ME01","44 STRETFORDEND MANCHESTER",2024,2020,"ME","SABINA MA"),
(202,"JOSMY",2,"KTE20ME02","87 STRETFORDEND MANCHESTER",2024,2020,"ME","SABINA MA"),
(501,"ANNIE",1,"KTE20CSM01","37 STRETFORDEND MANCHESTER",2023,2019,"CSE","VIDYA N"),
(502,"ASHWIN",3,"KTE20CSM01","37 STRETFORDEND MANCHESTER",2023,2019,"ME","VIDYA N");

/*INSERT INTO student_emailId VALUES();

INSERT INTO student_phoneNo VALUES();*/

INSERT INTO faculty VALUES(1001,"VIPIN VASU","ASSISTANT PROFESSOR","2020-11-23",NULL),
(1002,"KAVITHA N","PROFESSOR","2018-07-18",NULL),
(1003,"VIDYA N","ASSOCIATE PROFESSOR","2008-11-03",NULL);

INSERT INTO faculty_emailId VALUES(1001,"vipinvasu@gmail.com"),
(1002,"kavithan@gmail.com"),
(1003,"vidyan@gmail.com");

INSERT INTO qualification VALUES (100,10,"DISTINCTION"),
(101,9,"FIRSTCLASS"),
(102,8,"SECONDCLASS"),
(201,7,"SECONDCLASS"),
(202,9,"FIRSTCLASS"),
(501,10,"DISTINCTION"),
(502,10,"DISTINCTION");

INSERT INTO project VALUES(101,"FACE RECOGNITION",1001,"ML",1),
(102,"ATTENDNCE APP",1002,"WEB",2),
(501,"ATTENDNCE MANAGER",1003,"WEB",2),
(502,"CLOUD GAMING",1003,"NEURALNET",2),
(201,"XXXXX",1003,"AI",2),
(101,"DATA MINING",1001,"ML",1),
(102,"FACE MASK ",1001,"ML",1);


/*CREATING VIEWS*/
CREATE VIEW facDetails as
SELECT *
FROM faculty NATURAL JOIN faculty_emailId;

CREATE VIEW Stud_qual as
SELECT *
FROM student NATURAL JOIN qualification;

CREATE VIEW Stud_project AS
SELECT *
FROM project NATURAL JOIN student;

/*QUERY 1 : The names, roll no and address of the students who have completed the course under a given
branch for each year.*/

SELECT stud_name,roll_no,stud_address
FROM student
WHERE branch="CSE"
ORDER BY passout_yr;

/*QUERY 2 : The names and roll nos of the students who completed the course for each year of pass out and
for each branch.*/

SELECT stud_name,roll_no,branch,passout_yr
FROM student
ORDER BY branch,passout_yr;

/* QUERY 3 : The details of projects under taken by the students of a particular branch.*/

SELECT *
FROM project NATURAL JOIN student
WHERE branch="CSE";

/*QUERY 4 : The name of the faculty who guided more than a specified no. of projects in each academic year. */

SELECT fac_id,fac_name,admn_yr,count(*) as no_of_projects
FROM faculty JOIN Stud_project ON fac_id = guide
WHERE (fac_id,admn_yr) IN (SELECT guide,admn_yr
                            FROM Stud_project
                            )
GROUP BY guide
HAVING count(*) >1
ORDER BY admn_yr;

/*QUERY 5 : The branch with highest academic performance, chosen for each academic year.*/

SELECT branch,passout_yr,avg(total)
FROM student NATURAL JOIN qualification
GROUP BY branch,passout_yr
HAVING avg(total) > ALL (    SELECT avg(total)
                            FROM student NATURAL JOIN qualification
                            GROUP BY branch,passout_yr)
ORDER BY passout_yr asc;

/*QUERY 6 : The details of the students who secured the highest total for each branch and for each academic
year.*/

SELECT *
FROM student NATURAL JOIN qualification
GROUP BY branch,passout_yr
HAVING max(total)
ORDER BY passout_yr;

/*QUERY 7 : The list of students who secured a given grade, for a given academic year.*/

SELECT stud_id,stud_name
FROM Stud_qual
WHERE grade="DISTINCTION" AND passout_yr=2024;

/*QUERY 8 : The list of projects undertaken in each department together with the project guide name and
emailid, for each academic year under a given core area.*/

SELECT distinct stud_id,title,branch,guide,fac_emailId,core_area,passout_yr
FROM Stud_project JOIN facDetails ON guide=fac_id;

/*QUERY 9 : The number of total grades for each branch of study and for each year of admission.*/

SELECT admn_yr,branch,count(distinct grade) as no_of_grades
FROM Stud_qual
GROUP BY admn_yr,branch;

/*QUERY 10 : The details of students in each branch admitted in a specified academic year.*/

SELECT stud_id,stud_name,roll_no,utyreg_no,stud_address,passout_yr,admn_yr,branch,cls_adv
FROM student
WHERE admn_yr=2020;

/*QUERY 11 : The details of the students, sorted on the basis of year of admission and branch of study.*/

SELECT *
FROM student
ORDER BY admn_yr,branch;

/*QUERY 12 : The best mark, worst mark and the avg mark for each branch for a given academic year.*/

SELECT max(total) as best_mark,min(total) as worst_mark,avg(total) as avg_mark,branch,passout_yr
FROM Stud_qual
WHERE passout_yr=2024
GROUP BY branch,passout_yr;

/*DROPPING THE VIEWS,TABLES AND DATABASE*/
drop table project;
drop table qualification;
drop table faculty_emailId;
drop table faculty;
drop table student_phoneNo;
drop table student_emailId;
drop table student;
drop database expt7;
