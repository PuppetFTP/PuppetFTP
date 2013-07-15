-- ================================== PUPPETFTP_CREDENTIAL
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (1,'user_list','Lister les utilisateurs');
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (2,'user_edit','Modifier les utilisateurs');
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (3,'user_delete','Supprimer les utilisateurs');
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (4,'server_list','Lister les serveurs');
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (5,'server_edit','Modifier les serveurs');
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (6,'server_delete','Supprimer les serveurs');
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (7,'access_list','Lister les accès aux serveurs');
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (8,'access_edit','Modifier les accès aux serveurs');
insert into PUPPETFTP_CREDENTIAL (ID,NAME,DESCRIPTION) values (9,'access_delete','Supprimer les accès aux serveurs');

-- ================================== PUPPETFTP_ROLE
insert into PUPPETFTP_ROLE (ID,NAME,DESCRIPTION) values (1, 'admin', 'Administrateur');
insert into PUPPETFTP_ROLE (ID,NAME,DESCRIPTION) values (2, 'user', 'Utilisateur standard');

-- ================================== PUPPETFTP_ROLE_CREDENTIAL
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,1);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,2);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,3);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,4);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,5);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,6);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,7);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,8);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (1,9);

insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (2,1);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (2,4);
insert into PUPPETFTP_ROLE_CREDENTIAL (PUPPETFTP_ROLE,PUPPETFTP_CREDENTIAL) values (2,7);

-- ================================== USER
insert into USER (ID,FIRSTNAME,LASTNAME,PASSWD,EMAIL,PUPPETFTP_ROLE,CREATED_AT) values (1,'Admin','Admin','admin','admin@puppet.ftp',1, datetime());

-- ================================== SERVER_CREDENTIAL
insert into SERVER_CREDENTIAL (ID,NAME,DESCRIPTION) values (1,'user_list','Lister les utilisateurs');
insert into SERVER_CREDENTIAL (ID,NAME,DESCRIPTION) values (2,'user_edit','Modifier les utilisateurs');
insert into SERVER_CREDENTIAL (ID,NAME,DESCRIPTION) values (3,'user_delete','Supprimer les utilisateurs');
insert into SERVER_CREDENTIAL (ID,NAME,DESCRIPTION) values (4,'config_read','Lire la configuration');
insert into SERVER_CREDENTIAL (ID,NAME,DESCRIPTION) values (5,'config_write','Modifier la configuration');

-- ================================== SERVER_ROLE
insert into SERVER_ROLE (ID,NAME,DESCRIPTION) values (1, 'admin', 'Super administrateur');
insert into SERVER_ROLE (ID,NAME,DESCRIPTION) values (2, 'conf_manager', 'Administrateur (configuration)');
insert into SERVER_ROLE (ID,NAME,DESCRIPTION) values (3, 'user_manager', 'Administrateur (utilisateurs)');

-- ================================== SERVER_ROLE_CREDENTIAL
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (1, 1);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (1, 2);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (1, 3);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (1, 4);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (1, 5);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (2, 4);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (2, 5);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (3, 1);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (3, 2);
insert into SERVER_ROLE_CREDENTIAL (SERVER_ROLE, SERVER_CREDENTIAL) values (3, 3);


