create database expt6;
use expt6;

create table branch(
branch_id int PRIMARY KEY,
branch_name varchar(30),
branch_city varchar(10));

create table customer(
cust_id int PRIMARY KEY,
cust_name varchar(30),
cust_city varchar(10));

create table savings(
cust_id int,
branch_id int,
saving_accno int,
balance int,
foreign key(cust_id) references customer(cust_id),
foreign key(branch_id) references branch(branch_id));

create table loan(
cust_id int,
branch_id int,
loan_accno int,
balance int,
foreign key(cust_id) references customer(cust_id),
foreign key(branch_id) references branch(branch_id));

insert into branch values
(401,"Thiruvananthapuram","Thiruvananthapuram"),
(402,"Kottayam","Kottayam"),
(403,"Ernakulam","Kochi"),
(404,"Kozhikode","Kozhikode");

insert into customer values
(6001,"Ananthakrishnan","Thiruvananthapuram"),
(6002,"Irfan","Thiruvananthapuram"),
(6003,"Suneeth","Thiruvananthapuram"),
(6004,"Sreejith","Kottayam"),
(6005,"Jafar","Kazhakoottam"),
(6006,"Radika","Pampady"),
(6007,"Jameela","Kanjikuzhi"),
(6008,"Bindu","Kottayam"),
(6009,"Purushothaman","Kollam"),
(6010,"Vincy","Kottayam"),
(6011,"Abdul Rahman","Thrissur"),
(6012,"Vishwanathan","Ernakulam"),
(6013,"Marykutty","Mattancheri"),
(6014,"Hajara","Ernakulam"),
(6015,"Revathy","Kozhikode"),
(6016,"Hameed","Perambra"),
(6017,"Suchithra","Kozhikode"),
(6018,"Saneesh","North Paravoor"),
(6019,"Gokul Das","Kozhikode"),
(6020,"Abraham","Kappad");

insert into savings values
(6001,401,6400101,15000),
(6002,401,6400102,200000),
(6005,401,6400105,30000),
(6007,401,6400107,70000),
(6004,402,6400204,400000),
(6006,402,6400206,100000),
(6007,402,6400207,40000),
(6008,402,6400208,74000),
(6010,402,6400210,128507),
(6011,403,6400311,700000),
(6001,403,6400301,200000),
(6012,403,6400312,500000),
(6013,403,6400313,250000),
(6015,404,6400415,100000),
(6016,404,6400416,90756);

insert into loan values
(6005,401,4600105,100000),
(6003,401,4600103,200000),
(6009,401,4600109,150000),
(6019,401,4600119,100000),
(6011,403,4600311,1000000),
(6013,403,4600313,500000),
(6014,403,4600314,300000),
(6018,403,4600318,300000),
(6006,403,4600306,100000),
(6009,403,4600309,200000),
(6014,404,4600414,100000),
(6016,404,4600416,150000),
(6017,404,4600417,200000),
(6019,404,4600419,300000),
(6020,404,4600419,400000),
(6008,404,4600408,100000);

create view AllSaving as
SELECT *
FROM (branch NATURAL JOIN customer) NATURAL JOIN savings;

create view AllLoan as
SELECT *
FROM (branch NATURAL JOIN customer) NATURAL JOIN loan;

create view AllAcc as
SELECT AllSaving
UNION
SELECT AllLoan;


