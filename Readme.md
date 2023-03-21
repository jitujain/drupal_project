This project can be ran using [Docksal](https://docs.docksal.io/getting-started/setup)
or [Lando](https://docs.lando.dev/).

Specific instructions for both approaches are below, but prior to doing either,
this project requires Terminus [to be installed](https://pantheon.io/docs/terminus) on your host.

Follow [Terminus Github](https://github.com/pantheon-systems/terminus) to install
Terminus and verify your Pantheon account.

# Install project with Docksal

## Install Docksal
**This is a one time setup - skip this if you already have a working Docksal environment.**

Follow [Docksal environment setup instructions](https://docs.docksal.io/getting-started/setup)

## Install Pantheon rsync plugin.
Follow [Terminus rsync plugin](https://github.com/pantheon-systems/terminus-rsync-plugin)
- `mkdir -p ~/.terminus/plugins`
- `composer create-project --no-dev -d ~/.terminus/plugins pantheon-systems/terminus-rsync-plugin:~1`

To use `terminus` a machine token generated from your Pantheon account settings is required.

## Project setup
1. Ensure you delete or backup your settings.local.php to allow Docksal to generate
own settings.local.php file. This is needed only on first project installation.

2. Create a `docksal-local.env` file inside `.docksal/`

3. Use `fin` command to create and set values for `HOSTING_SITE` and `HOSTING_ENV` variables.
  - `fin config set --env=local HOSTING_SITE="[site_name]"`
  - `fin config set --env=local HOSTING_ENV="[site_env]"`
    - `dev`, `test`, `live`

From terminal go to `docroot` folder and run command:

    `fin init` - project setup

## A list of useful Docksal commands
- `fin drush` - run Drush commands.
- `fin exec` - execute a shell command on cli service container.
- `fin sqlc` - connect to database trough command line.
- `fin help` - display all available commands.

## A list of commands to mange Docusign project
- `fin init` - rebuild Docksal environment and install Docusign project (will run all below commands except `files-sync`).
- `fin update-database` - download a fresh copy of Pantheon database and import it.
- `fin files-sync` - synchronize files directory from Pantheon.
  - Due the size of the files directory, `stage_file_proxy` should be used instead.
- `fin local-settings` - config and modules overrides for local development.
- `fin phpcs` - run code sniffers.
- `fin test` - run tests.

## Apache Solr
For Apachesolr module add your Solr server using following server url:

    http://solr:8983/solr

https://docs.docksal.io/en/master/tools/apache-solr/

## Mail via MailHog
Send and capture local sent emails using MailHog service.

Available under URL: http://mail.docusign.docksal

## Docusign frontend

### Install frontend dependencies:
    fin frontend

### Compile SCSS files:

    fin frontent

### Watch and compile any changes:
    fin frontend watch

## Docusign Specific Issues

### Location of Project Folder

Make sure project folder is under User directory somewhere.

### Removing Vagrant files

Preferably, start with a clean pull from the Repo into a new project folder.

If using the same project folder that Vagrant was on, you will need remove setting.local.php & copy example.setting.local.php in it’s place

### Update rsync to version 3

Check your version of rsync in terminal with

`/usr/local/bin/rsync --version`

If using older than version 3, you will need to upgrade.

If using Homebrew (easiest way):

   `brew install rsync`

If not:

    cd ~/Desktop

    curl -O http://rsync.samba.org/ftp/rsync/rsync-3.1.1.tar.gz

    tar -xzvf rsync-3.1.1.tar.gz

    rm rsync-3.1.1.tar.gz

    cd ~/Desktop/rsync-3.1.1

    ./prepare-source

    ./configure

    make

    sudo make install

    sudo mv /usr/local/bin/rsync /usr/bin

### Issue with files-sync

Create ssh and add to Aquia

`ssh-keygen -b 4096` —DO NOT ADD passphrase

`pbcopy < ~/.ssh/id_rsa.pub` -copies the key

Paste into Aquia SSH keys section

**Note: There is a delay until it’s deployed to the server**


### More info
https://docs.docksal.io/en/master

# Install project with Lando

## Install Lando

Follow the instructions on the [Lando installation page](https://docs.lando.dev/getting-started/installation.html)
and install in a way appropriate for your operating system.
With OSX, Homebrew is the fastest and smoothest method: `brew install --cask lando`
With Windows, downloading the `.exe` file from [the Github page](https://github.com/lando/lando/releases)
is easiest.

## Project Setup

From the `/web` directory in this repository, run the following:

* `lando start`

## Syncing database and files

Lando has a straightforward `pull` function that can be used to get the latest
database and files from any of the three environments on Pantheon.

**Note**: You will need to have Terminus set up and authenticated via token for
this function to work.

`lando pull --code=none --database=live --files=live`

If you prefer to get the database from the Test or Dev environments, replace the
word `live` with `test` or `dev`, respectively.

**Note**: because this codebase is hosted separately from Pantheon, you are
extremely unlikely to need to ever run `--code=live` or similar.

After successfully pulling the database, run `lando drush cc all` to clear the cache.

## Useful Lando functions

* `lando pull` to get a database or set of files.
* `lando drush` to run any Drush commands
* `lando rebuild` to rebuild the Lando environment
* `lando stop` to shut down the container.

## Additional Configuration

The Lando configuration is stored in .lando.yml; this designates settings that
will be universal to anyone running Lando for this project. If you want to add
additional configuration options for your local environment, create `.lando.local.yml`
and add parameters there.
