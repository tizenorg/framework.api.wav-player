#sbs-git:slp/api/wav-player capi-media-wav-player 0.1.0 8d904bb3bd0ca7fa01ebd8f4185e4b993d94c08d
Name:       capi-media-wav-player
Summary:    A wav player library in SLP C API
Version:    0.1.19
Release:    0
Group:      libdevel
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(mm-sound)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(capi-media-sound-manager)
Requires(post): /sbin/ldconfig  
Requires(postun): /sbin/ldconfig
Requires(post): libprivilege-control

%description


%package devel
Summary:  A wav player library in SLP C API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel


%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
mkdir -p %{buildroot}/usr/share/privilege-control

%make_install

%post
/sbin/ldconfig
/usr/bin/api_feature_loader --verbose --dir=/usr/share/privilege-control

%postun -p /sbin/ldconfig


%files
%{_libdir}/libcapi-media-wav-player.so.*
%{_datadir}/license/%{name}
%manifest capi-media-wav-player.manifest

%files devel
%{_includedir}/media/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-media-wav-player.so
