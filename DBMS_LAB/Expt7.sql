/*AUTHOR - NAVYA.S.RAJ
BATCH - S5 CSE
ROLL NO. - 51
SUBJECT - DBMS LAB*/

/*CREATING THE DATABASE*/
create database expt7;
use expt7;

/*CREATING THE TABLES*/
create table student(
stud_name varchar(20),
roll_no int(2),
utyreg_no int PRIMARY KEY,
branch varchar(5),
admn_yr int,
passout_yr int,
cls_tchr varchar(15),
phone_no int(10)
);

create table student_emailId(
utyreg_no int,
stud_emailId varchar(30),
FOREIGN KEY(utyreg_no) references student(utyreg_no),
PRIMARY KEY(stud_name,stud_emailId)
);

create table student_address(
utyreg_no int,
address varchar(50),
FOREIGN KEY(utyreg_no) references student(utyreg_no),
PRIMARY KEY(stud_name,address)
);

/*create table student_phoneNo(
utyreg_no int,
phoneNo varchar(30),
FOREIGN KEY(utyreg_no) references student(utyreg_no),
PRIMARY KEY(stud_name,phoneNo)
);*/

create table faculty(
fac_id int PRIMARY KEY,
fac_name varchar(20),
designation varchar(15),
join_date date,
relieved_date date
);

create table faculty_emailId(
fac_id int,
fac_emailId varchar(30),
FOREIGN KEY(fac_id) references faculty(fac_id),
PRIMARY KEY(fac_id,fac_emailId)
);

create table qualification(
utyreg_no int,
total int,
grade char(1),
FOREIGN KEY(utyreg_no) references student(utyreg_no),
PRIMARY KEY(utyreg_no,total)
);

create table project(
utyreg_no int,
title varchar(10),
core_area varchar(10),
guide varchar(10),
prd_of_impl int,
FOREIGN KEY(utyreg_no) references student(utyreg_no),
PRIMARY KEY(utyreg_no,title)
);

create table teaches(
utyreg_no int,
fac_id int
);

create table guides(
utyreg_no int,
fac_id int,
title varchar(10)
);


/*DROPPING THE VIEWS,TABLES AND DATABASE*/
drop table guides;
drop table teaches;
drop table project;
drop table qualification;
drop table faculty_EmailId;
drop table faculty;
drop table student_address;
drop table student_emailId;
drop table student;
drop database expt7;
