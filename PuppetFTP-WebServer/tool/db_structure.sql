--==============================================================
-- Nom de SGBD :  ANSI Level 2
-- Date de création :  06/01/2013 23:58:31
--==============================================================

--==============================================================
-- Table : PUPPETFTP_ROLE
--==============================================================
create table PUPPETFTP_ROLE (
ID                   INTEGER              not null,
NAME                 VARCHAR(64)          not null,
DESCRIPTION          VARCHAR(256)         not null,
primary key (ID)
);

--==============================================================
-- Table : "USER"
--==============================================================
create table "USER" (
ID                   INTEGER              not null,
FIRSTNAME            VARCHAR(64),
LASTNAME             VARCHAR(64),
PASSWD               VARCHAR(32)          not null,
EMAIL                VARCHAR(1024)        not null,
PUPPETFTP_ROLE       INTEGER              not null,
CREATED_AT           DATE                 not null,
LAST_ACCESS          DATE,
primary key (ID),
foreign key (PUPPETFTP_ROLE)
      references PUPPETFTP_ROLE (ID)
);

--==============================================================
-- Table : SERVER
--==============================================================
create table SERVER (
ID                   INTEGER              not null,
NAME                 VARCHAR(256),
ADDRESS              VARCHAR(63)          not null,
PORT                 INTEGER,
CORBA_ID	     VARCHAR(100)	  not null,
primary key (ID)
);

--==============================================================
-- Table : SERVER_ROLE
--==============================================================
create table SERVER_ROLE (
ID                   INTEGER              not null,
NAME                 VARCHAR(64)          not null,
DESCRIPTION          VARCHAR(256)         not null,
primary key (ID)
);

--==============================================================
-- Table : ACCESSIBLE_SERVER
--==============================================================
create table ACCESSIBLE_SERVER (
"USER"               INTEGER              not null,
SERVER               INTEGER              not null,
SERVER_ROLE          INTEGER              not null,
primary key (SERVER, "USER", SERVER_ROLE),
foreign key ("USER")
      references "USER" (ID),
foreign key (SERVER)
      references SERVER (ID),
foreign key (SERVER_ROLE)
      references SERVER_ROLE (ID)
);

--==============================================================
-- Index : ACCESSIBLE_SERVER_PK
--==============================================================
create unique index ACCESSIBLE_SERVER_PK on ACCESSIBLE_SERVER (
SERVER ASC,
"USER" ASC,
SERVER_ROLE ASC
);

--==============================================================
-- Index : RELATION_6_FK
--==============================================================
create  index RELATION_6_FK on ACCESSIBLE_SERVER (
"USER" ASC
);

--==============================================================
-- Index : RELATION_7_FK
--==============================================================
create  index RELATION_7_FK on ACCESSIBLE_SERVER (
SERVER ASC
);

--==============================================================
-- Index : RELATION_8_FK
--==============================================================
create  index RELATION_8_FK on ACCESSIBLE_SERVER (
SERVER_ROLE ASC
);

--==============================================================
-- Table : PUPPETFTP_CREDENTIAL
--==============================================================
create table PUPPETFTP_CREDENTIAL (
ID                   INTEGER              not null,
NAME                 VARCHAR(64)          not null,
DESCRIPTION          VARCHAR(256)         not null,
primary key (ID)
);

--==============================================================
-- Index : CREDENTIAL_PK2
--==============================================================
create unique index CREDENTIAL_PK2 on PUPPETFTP_CREDENTIAL (
ID ASC
);

--==============================================================
-- Index : ROLE_PK2
--==============================================================
create unique index ROLE_PK2 on PUPPETFTP_ROLE (
ID ASC
);

--==============================================================
-- Table : PUPPETFTP_ROLE_CREDENTIAL
--==============================================================
create table PUPPETFTP_ROLE_CREDENTIAL (
PUPPETFTP_CREDENTIAL INTEGER              not null,
PUPPETFTP_ROLE       INTEGER              not null,
primary key (PUPPETFTP_CREDENTIAL, PUPPETFTP_ROLE),
foreign key (PUPPETFTP_ROLE)
      references PUPPETFTP_ROLE (ID),
foreign key (PUPPETFTP_CREDENTIAL)
      references PUPPETFTP_CREDENTIAL (ID)
);

--==============================================================
-- Index : ROLE_CREDENTIAL_PK2
--==============================================================
create unique index ROLE_CREDENTIAL_PK2 on PUPPETFTP_ROLE_CREDENTIAL (
PUPPETFTP_CREDENTIAL ASC,
PUPPETFTP_ROLE ASC
);

--==============================================================
-- Index : RELATION_2_FK2
--==============================================================
create  index RELATION_2_FK2 on PUPPETFTP_ROLE_CREDENTIAL (
PUPPETFTP_ROLE ASC
);

--==============================================================
-- Index : RELATION_3_FK2
--==============================================================
create  index RELATION_3_FK2 on PUPPETFTP_ROLE_CREDENTIAL (
PUPPETFTP_CREDENTIAL ASC
);

--==============================================================
-- Index : SERVER_PK
--==============================================================
create unique index SERVER_PK on SERVER (
ID ASC
);

--==============================================================
-- Table : SERVER_CREDENTIAL
--==============================================================
create table SERVER_CREDENTIAL (
ID                   INTEGER              not null,
NAME                 VARCHAR(64)          not null,
DESCRIPTION          VARCHAR(256)         not null,
primary key (ID)
);

--==============================================================
-- Index : CREDENTIAL_PK
--==============================================================
create unique index CREDENTIAL_PK on SERVER_CREDENTIAL (
ID ASC
);

--==============================================================
-- Index : ROLE_PK
--==============================================================
create unique index ROLE_PK on SERVER_ROLE (
ID ASC
);

--==============================================================
-- Table : SERVER_ROLE_CREDENTIAL
--==============================================================
create table SERVER_ROLE_CREDENTIAL (
SERVER_CREDENTIAL    INTEGER              not null,
SERVER_ROLE          INTEGER              not null,
primary key (SERVER_CREDENTIAL, SERVER_ROLE),
foreign key (SERVER_ROLE)
      references SERVER_ROLE (ID),
foreign key (SERVER_CREDENTIAL)
      references SERVER_CREDENTIAL (ID)
);

--==============================================================
-- Index : ROLE_CREDENTIAL_PK
--==============================================================
create unique index ROLE_CREDENTIAL_PK on SERVER_ROLE_CREDENTIAL (
SERVER_CREDENTIAL ASC,
SERVER_ROLE ASC
);

--==============================================================
-- Index : RELATION_2_FK
--==============================================================
create  index RELATION_2_FK on SERVER_ROLE_CREDENTIAL (
SERVER_ROLE ASC
);

--==============================================================
-- Index : RELATION_3_FK
--==============================================================
create  index RELATION_3_FK on SERVER_ROLE_CREDENTIAL (
SERVER_CREDENTIAL ASC
);

--==============================================================
-- Index : USER_PK
--==============================================================
create unique index USER_PK on "USER" (
ID ASC
);

