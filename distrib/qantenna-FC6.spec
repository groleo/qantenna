Summary: Qt based program for viewing antennas as decribed by NEC files.
Name: qantenna
Version: 0.2
Release: 1
License: GPL
Group: Applications/Engineering
Source: http://puzzle.dl.sourceforge.net/sourceforge/qantenna/qantenna-0.2.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot

%description
QAntenna is able to show antennas in a 3D plot, and calculate it's
radiation pattern. It is capable of working with many antennas at
the same time.

%prep

%setup -q

%build
rm -rf Makefile src/Makefile src/cards/Makefile
qmake-qt4 PREFIX=/usr qantenna.pro
make RPM_OPT_FLAGS="$RPM_OPT_FLAGS"

%install
rm -rf $RPM_BUILD_ROOT
make INSTALL_ROOT=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc README AUTHORS COPYING ChangeLog

/usr/bin/qantenna
/usr/share/qantenna/*
/usr/share/doc/qantenna/*

%changelog
* Wed Apr 04 2007 Joop Stakenborg <pg4i@amsat.org>
- initial spec file

