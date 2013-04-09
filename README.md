# PuppetFTP

##1. Dependencies

   * Qt 4.8.x
   * OmniORB 4.6 (omniNames)
   * SQLite 3

NOTE: Ensure your environment is correctly set. In order to build the project, you need Qt tools (qmake) and libraries. For onmiNames, you may set  the LD_LIBRARY_PATH environment variable to the path where is installed OmniORB.

##2. Building

   * The web server:
	   * cd PuppetFTP-WebServer
	   * qmake
	   * make

   * For the daemon
	   * cd PuppetFTP-Daemon
	   * qmake
	   * make

Binaries can be found in their bin folder.

##3. Configuration

#### Webserver

A default configuration is provided, you do not need to modify it. The configuration file is located in **bin/config/config.ini**

Parameters:

 * **HostAddress**    => Host address, used for listening web request. Default ANY

 * **HostPort**       => Default port used to listen web request. Default 5074

 * **SessionTimeout** => Session timeout, default timeout for web session. Default 1200

 * **InitRef**        => Parameter used to configure CORBA and Naming service location. Default: NameService=corbaloc:iiop:localhost:2809/NameService

#### Daemon

You will have to edit the configuration file in order to set the identifier of the daemon. Others parameters do not need to be edited. The configuration file is located in **bin/config.ini**. You must copy and paste this configuration file next to the daemon binary.

 * server_name    => Identifier of the daemon over the network, this name must be unique and must match the one mentionned on the web server. By default, it is set to localhost, you will have to change it if you want to manage several servers.

 * conf_file      => Configuration file of the managed server. Refer to the documentation of the server for more informations. Path must be absolute.

 * plugin_path    => Path to the plugin to be loaded. You have to tell which plugin to load to manage your server. Only vsftpd and proftpd are currently supported, plugins are respectively libvsftpd.so and libproftpd.so and are located in bin/plugins. Path must be absolute.

##4. Execution

 * start CORBA Naming service with: omniNames **-start** **-always** **-logdir** \<logdir\> **&**
  
 * start the daemon on the managed server. The daemon is a service,
  simple run the following to start it: **./puppetFtpd**

 * start the web server, run : **./PuppetFTP-WebServer &**

 * to stop the service run: **./puppetFtpd -t**


#Known issue : 

- On Rhel based distros, there is a known issue preventing us from restarting services.
