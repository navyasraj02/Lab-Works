/*AUTHOR - NAVYA.S.RAJ
BATCH - S5 CSE
ROLL NO. - 51
SUBJECT - DBMS LAB*/

/*CREATING THE DATABASE*/
create database expt6;
use expt6;

/*CREATING THE TABLES*/
create table branch(
branch_id int PRIMARY KEY,
branch_name varchar(30),
branch_city varchar(30));

create table customer(
cust_id int PRIMARY KEY,
cust_name varchar(30),
cust_city varchar(30));

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

/*POPULATING THE DATABASE*/
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


/*CREATING VIEWS*/
create view AllSaving as
SELECT *
FROM (branch NATURAL JOIN customer) NATURAL JOIN savings;

create view AllLoan as
SELECT *
FROM (branch NATURAL JOIN customer) NATURAL JOIN loan;

create view AllAcc(branch_id,cust_id,branch_name,branch_city,cust_name,cust_city,accno,balance) as
SELECT *
FROM AllSaving
UNION
SELECT *
FROM AllLoan;

\! echo '------------AllSaving view-------------'
SELECT *
FROM AllSaving;
\! echo '------------AllLoan view-------------'
SELECT *
FROM AllLoan;
\! echo '------------AllAcc view-------------'
SELECT *
FROM AllAcc;


/*Query 1 : List out the details of the customers who live in the same city as they have savings or loan account.*/
\! echo '------------Query 1-------------'
SELECT cust_id,cust_name,cust_city,branch_city
FROM AllAcc
WHERE branch_city=cust_city;


/*Query 2 : List out the customers who have an account in a given branch-city*/
\! echo '------------Query 2-------------'
SELECT cust_id,cust_name
FROM AllAcc
WHERE branch_city="Kottayam";


/*Query 3 : List out the customers who have an account in more than one branch*/
\! echo '------------Query 3-------------'
SELECT cust_id,cust_name
FROM AllAcc
GROUP BY cust_id,cust_name
HAVING count(*)>1;


/*Query 4(i) : List out details of the customer who have neither a saving account but a loan */
\! echo '------------Query 4(i)-------------'
SELECT cust_id,cust_name
FROM AllLoan 
WHERE  cust_id NOT IN(		SELECT cust_id
				FROM AllSaving);
				
				
/*Query 4(ii) : List out details of the customer neither a loan but has a saving account.*/
\! echo '------------Query 4(ii)-------------'
SELECT cust_id,cust_name
FROM  AllSaving
WHERE  cust_id NOT IN(		SELECT cust_id
				FROM AllLoan );
				
				
/*Query 4(iii) : List out details of the customer having both loan and saving.*/				
\! echo '------------Query 4(iii)-------------'						
SELECT L.cust_id,L.cust_name
FROM  AllSaving as S,AllLoan as L
WHERE L.cust_id=S.cust_id;


/*Query 5 : List the names of the customers who have no saving at all but having loan in more than two branches*/
\! echo '------------Query 5-------------'
SELECT cust_name
FROM AllLoan
GROUP BY cust_id
HAVING count(*)>2;               /*In the dataset,there are no customers having loan in more than 2 branches */


/*Query 6 :For each branch produce a list of the total number of customers, total number of customers with
loan only, total number of customers with saving only and the total number of customers with both
loan and saving.*/
\! echo '------------Query 6------------'
create view C_loan as
SELECT DISTINCT L.branch_id,count(*) as no_l
FROM AllLoan as L
WHERE L.cust_id NOT IN (SELECT S.cust_id FROM AllSaving as S WHERE L.branch_id=S.branch_id)
GROUP BY L.branch_id;

create view C_saving as
SELECT DISTINCT S.branch_id,count(*) as no_s
FROM AllSaving as S
WHERE S.cust_id NOT IN (SELECT L.cust_id FROM AllLoan as L WHERE L.branch_id=S.branch_id)
GROUP BY S.branch_id;

create view C_both as
SELECT DISTINCT S.branch_id,count(*) as no_both
FROM AllSaving as S,AllLoan as L
WHERE L.branch_id=S.branch_id AND L.cust_id=S.cust_id
GROUP BY L.branch_id;

SELECT B.branch_id,B.branch_name,
	ifnull(L.no_l,0) as no_of_cust_loans_only,
	ifnull(S.no_s,0) as no_of_cust_savings_only,
	ifnull(Bo.no_both,0) as no_of_cust_both,
	ifnull(L.no_l,0) + ifnull(S.no_s,0)+ifnull(Bo.no_both,0) as total_no_of_cust
FROM branch as B
LEFT JOIN C_loan as L ON B.branch_id=L.branch_id
LEFT JOIN C_saving as S ON B.branch_id=S.branch_id
LEFT JOIN C_both as Bo ON B.branch_id=Bo.branch_id;


/*Query 7 : Find the details of the branch which has issued max amount of loan*/
\! echo '------------Query 7------------'	
SELECT L.branch_id,L.branch_name,count(*) as loans_issued
FROM AllLoan as L
GROUP BY branch_id
ORDER BY loans_issued DESC
LIMIT 1;


/*Query 8 : Find the details of the branch which has not yet issued any loan at all.*/
\! echo '------------Query 8------------'
SELECT B.branch_id,B.branch_name
FROM branch as B
WHERE B.branch_id NOT IN (SELECT L.branch_id FROM AllLoan As L);


/*Query 9 : For each customer produce a list consisting of the total saving balance, loan balance for those branches
where he has either a loan or a saving account or both.*/
\! echo '------------Query 9------------'
create view cust_details as 
SELECT C.cust_id,C.cust_name,
	ifnull(L.balance,0) as l_balance,
	ifnull(S.balance,0) as S_balance
FROM AllAcc as C
LEFT JOIN AllLoan as L ON L.loan_accno=C.accno
LEFT JOIN AllSaving as S ON S.saving_accno=C.accno;

SELECT cust_id,cust_name,sum(l_balance) as loan_balance,sum(s_balance) as savings_balance
FROM cust_details
GROUP BY cust_id,cust_name;


/*DROPPING THE VIEWS,TABLES AND DATABASE*/
drop view cust_details;
drop view C_loan;
drop view C_saving;
drop view C_both;
drop view AllAcc;
drop view AllLoan;
drop view AllSaving;
drop table loan;
drop table savings;
drop table customer;
drop table branch;
drop database expt6;
