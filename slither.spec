%define gh_user giosali

Name:           slither
Version:        1.0.1
Release:        9%{?dist}
Summary:        An application for Linux that allows you to simulate keyboard shortcuts with touchpad gestures

License:        MIT
URL:            https://github.com/%{gh_user}/%{name}
Source0:        %{url}/archive/v%{version}.tar.gz
Source1:        slither.desktop
Source2:        slither-autostart.desktop

BuildRequires:  gcc-c++
BuildRequires:  cmake >= 3.28
BuildRequires:  make
BuildRequires:  libinput-devel
BuildRequires:  libudev-devel
BuildRequires:  libevdev-devel
BuildRequires:  spdlog-devel
BuildRequires:  wxGTK3
BuildRequires:  wxGTK-devel
BuildRequires:  desktop-file-utils
BuildRequires:  systemd-rpm-macros

Requires:       libinput
Requires:       libevdev
Requires:       spdlog
Requires:       wxGTK3

%description
Slither is a touchpad utility application designed for Linux (GNOME on Wayland). 
With Slither, you can streamline your workflow by transforming touchpad gestures 
into keyboard combinations to boost your productivity.

%prep
%autosetup

%build
%cmake -DCMAKE_BUILD_TYPE=Release
%cmake_build

%install
%cmake_install

# Install desktop file
desktop-file-install --dir=%{buildroot}%{_datadir}/applications %{SOURCE1}

# Install autostart desktop file
install -Dm644 %{SOURCE2} %{buildroot}%{_sysconfdir}/xdg/autostart/%{SOURCE2}

# Install icon
install -Dm644 slither.png %{buildroot}%{_datadir}/pixmaps/slither.png

%post
setcap cap_dac_override=ep %{_bindir}/slither || :

%files
%license LICENSE
%doc README.md
%{_bindir}/%{name}
%{_datadir}/applications/slither.desktop
%{_sysconfdir}/xdg/autostart/slither-autostart.desktop
%{_datadir}/pixmaps/slither.png

%changelog
* Sun Dec 14 2025 giosali <gio_sali@outlook.com> - 1.0.1-2
- Switch to system service with proper capability handling
- Add systemd scriptlets for proper service management

* Sun Dec 14 2025 giosali <gio_sali@outlook.com> - 1.0.1-1
- Change ExecStart value

* Sun Dec 14 2025 giosali <gio_sali@outlook.com> - 1.0.0-2
- Remove libudev dependency

* Sun Dec 14 2025 giosali <gio_sali@outlook.com> - 1.0.0-1
- Update for COPR distribution
- Add systemd user service
- Add desktop file integration
- Set required capabilities

* Fri Nov 01 2024 giosali <gio_sali@outlook.com> - 1.0.0
- Initial release