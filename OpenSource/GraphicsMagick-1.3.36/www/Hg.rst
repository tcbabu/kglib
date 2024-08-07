.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See http://docutils.sourceforge.net/rst.html for details.

=======================================
GraphicsMagick Mercurial
=======================================

.. meta::
   :description: GraphicsMagick is a robust collection of tools and libraries to read,
                 write, and manipulate an image in any of the more popular
                 image formats including GIF, JPEG, PNG, PDF, and Photo CD.
                 With GraphicsMagick you can create GIFs dynamically making it
                 suitable for Web applications.  You can also resize, rotate,
                 sharpen, color reduce, or add special effects to an image and
                 save your completed work in the same or differing image format.

   :keywords: GraphicsMagick, PerlMagick, visualization, image
              processing, software development, simulation, image,
              software, Magick++

.. _Mercurial : https://www.mercurial-scm.org/
.. _TortoiseHg : https://tortoisehg.bitbucket.io/
.. _`GraphicsMagick repository at SourceForge` : http://hg.code.sf.net/p/graphicsmagick/code/

.. contents::

The GraphicsMagick source code is available via Mercurial_. Mercurial_
is a convenient way for developers from around the country or world to
download the GraphicsMagick source, fix bugs, or add new features.
Due to the way Mercurial_ works, it may also be used to manage local
changes to GraphicsMagick.

What is Mercurial?
==================

Mercurial_ (also known as `Hg` due to the abbreviation for Mercury in
the periodic table of the elements) is a modern source control system
which provides anyone who clones a repository with a stand-alone local
repository containing the full development history and the ability to
select any version of the code.  Since the local repository is
fully-functional, you may use the same repository to manage your local
changes to GraphicsMagick code and you may use the repository to share
your changes with others.

Web Access
=============

The `GraphicsMagick repository at SourceForge`_ web interface is
available which may be used to interactively view the latest versions
of files, or the changes to files, using your web browser.

Cloning the Mercurial Repository
==================================

To get the tree and place it in a sub-directory of your current working
directory, issue the command::

  hg clone http://hg.code.sf.net/p/graphicsmagick/code GM

Please note that since the introduction of an HTTP load balancer,
SourceForge has become unreliable when cloning with the default http
protocol.  Due to this, using ssh protocol may be required.  Any
SourceForge user who has submitted a SSH private key to SourceForge
may use Mercurial over SSH to clone the repository.  The ssh clone
syntax looks like this (replacing `YOURID` with your SourceForge user
name):

  hg clone ssh://YOURID@hg.code.sf.net/p/graphicsmagick/code GM

Selecting a version of the code
========================================

By default the cloned directory is populated with files from the
`default` (i.e. head) branch of the code, which is where active
development happens.

If you require a specific release of GraphicsMagick (e.g. 1.3.23), you may select it like::

  hg update -r GraphicsMagick-1_3_23

or if you require a specific branch of GraphicsMagick (e.g. 1.3), you may use::

  hg update -r GraphicsMagick-1_3

or you may request the files which were current on a specific date::

  hg update -d 2009-01-14

Use::

  hg branches

to see the available branches, and::

  hg tags

to see the available release tags.

Updating from the Mercurial Repository
========================================

To pull more changes from the repository, execute::

  hg pull

and to make them visible in your files (via a merge), execute::

  hg update

or just::

  hg pull -u

The latter pulls down any updates into your local repository and
automatically does a merge.

Mercurial Software
==================

The best place to look for the latest version of Mercurial (`Hg`) is
at the Mercurial_ web site.  Most free operating systems (e.g. Linux,
OpenIndiana, and \*BSD) will offer a version of Mercurial as an
installable package and it may already be installed on your system.
We recommend use of TortoiseHg_ on Microsoft Windows systems since it
provides a very nice graphical interface.  TortoiseHg_ is also
available on Linux and other systems.

Mercurial for GraphicsMagick Developers
========================================

Since Mercurial_ is a distributed revision control system, you may
clone the GraphicsMagick repository and work for days or weeks (making
your own local commits) before you decide to push some or all of your
changes to the GraphicsMagick development repository.  GraphicsMagick
developers first commit changes to their own local respository, then
they push their changes to the GraphicsMagick development repository
at hg.graphicsmagick.org, later on (after testing and possible fixes)
I will push the changes to the stable repository at SourceForge.
Pushes to the stable repository at SourceForge should occur at least
as often as source code snapshots are produced.

The repository hierarchy is as follows:

1. Local

  The developer makes any local changes and commits what he likes in his
  own repository.  It is best to commit often and whenever all the
  files have been updated to implement a coherent change or feature
  (including the ChangeLog file!) since Mercurial_ stores related
  changes as a changeset along with the change message you enter.
  When you push your repository, these changesets and messages are
  preserved.

2. Unstable

  The unstable development repository is available via ssh at
  "ssh://yourid@hg.GraphicsMagick.org//hg/GraphicsMagick".

  Where `yourid` is the Unix user ID on the GraphicsMagick server.
  The `yourid@` part may left out if your client system uses the same
  user ID as on the GraphicsMagick server.

3. Stable

  The stable repository is available via http at
  "http://hg.code.sf.net/p/graphicsmagick/code".  Any changes in the
  unstable development repository are pushed to the stable repository
  (by the developer responsible for this role) once any necessary
  adjustments have been made, documentation files have been generated,
  and the software test suite has passed on at least one machine.

To build your local development repository (as quickly as possible),
you may use these steps:

1. Clone the stable respository at SourceForge::

     hg clone http://hg.code.sf.net/p/graphicsmagick/code GM

2. Adjust your local repository path default to use the unstable repository.

   Edit .hg/hgrc in your local repository so that it contains::

     [paths]
     default = ssh://yourid@hg.GraphicsMagick.org//hg/GraphicsMagick

   where `yourid` is the Unix user ID on the GraphicsMagick server.

3. Pull any additional pending updates from the unstable repository::

     hg pull -u

Please note that when ssh access is used, Mercurial uncompresses any
data and sends it in uncompressed form.  Mercurial expects that
compression will be enabled in ssh when needed.  One way to enable ssh
compression is to put this in your local .hgrc::

  [ui]
  ssh = ssh -C

but ssh also provides its own way to enable compression on a
site-by-site basis (e.g. via .ssh/config).  For example an entry in
.ssh/config will enable use of compression::

  Host hg.GraphicsMagick.org
    Compression yes

SSH Public Keys For hg.GraphicsMagick.org
=========================================

For reference, these are the ssh public keys for the server at hg.GraphicsMagick.org:

DSS (DSA)::

  ssh-dss AAAAB3NzaC1kc3MAAACBANZAsDZ9fUWQNwUoRw8HoNl8aLLs97KmyiaA6mSPeM1NeQKrxk0PAFEXMR05CNcZHSyopUx6B8PuTWE4+4rDhFCw7J0JkfFS4uIG3bu3YCRqQrg2k4VsDw60zK9sNum5BcLEWd+qs8X7DrEff5fGmXkc8IdMXPgHTzaJWCT9YJU1AAAAFQCJaFq4/7FqHcHm5abhW5qJyH0RgQAAAIEAgv6s3gfB8p/Elf0ZcIZ5eITCpI9aZFaSLSeKHMmhYps1uMuZ9LtWjZ11cotcuOh0tlwGUixlu/5soZqX6VbnJAuyvfI+7WSUFuJmRjsbXJVCBuSPZ7YgMNuLYlLst7sZLCs5hU61jxnaR2zmkUjDWP4GWROC6AYZXlbJX1qRJ7YAAACBAMsIbVVgz/aP95yCPk1Pw0FjoL5t6C3BpxdA9aiIFBMg14ElaHh+gaXQoZfjAuafZ8pc5woYtQLLkzinCQnmvH/EqqYCe+Fu7jcsYU7oWUXG1O9ZBKI7QZkeCTaYMXIWBplgVD+tkRpH/gxn5iweNMM9e43qPB0b2JYObliqD1E9 root@src

RSA::

  ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEA1IuJDYT85qz/w6+vn5hkpzM5Ju5dsMeJD9GnATj3op5dhBWyfbaJpS7yyK2Vhhz26GBUvUtO3LGm0dQvdj83P3DX3aUuzfnC3Bc9dWeARomQPtDy9MfDikD6kqjD9/Lemgvv8I4Na9vUEmYvXUpTrtawJ4S7A7IctPnvKLPGA5+qY5XzMSE0wcOSBdbeV1PAIDOXYH2hKakZwtxXlvfTv6CZphz/jG5nmf+/Zlkr4yopNvPFbtd3vbaaqSuCoGHXKfmpRko2gXf6EGF92wXzbsE1tW3AkSJ2xdhFHRNmQEu2y9F1l9zb8IETBtKMWRJWAsPPpUSkht0DRsTXt/f+Zw== root@src

ECDSA::

  ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBOrGQ6tjmZvm8w+GP7yLFJ1/vkImKkpXv7kPNxA0+Sfx6WCqAjV0pWP5MVCraP8SNbphL8jiS/x3WADXlf+R2KQ= root@src

ED25519::

  ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIAtwIcJEBiSUWsB2sydInR76gE84Jp1rxmc8lTGPg5cB root@src


Email Notifications
===================

.. _`graphicsmagick-commit` : https://lists.sourceforge.net/lists/listinfo/graphicsmagick-commit

An email notification is sent to the `graphicsmagick-commit`_ mailing
list at SourceForge whenever a change is submitted to the development
(unstable) repository.  Subscribe to this list if you would like to be
notified by email of changes when they occur.


Mercurial Topics
====================

* `Merge Tool Configuration <https://www.mercurial-scm.org/wiki/MergeToolConfiguration>`_
* `Keep "My" or "Their" files when doing a merge <https://www.mercurial-scm.org/wiki/TipsAndTricks#Keep_.22My.22_or_.22Their.22_files_when_doing_a_merge>`_
