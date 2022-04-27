# --- CORDINATE SYSTEMS ---
#--------------------------------------------
# Module name:      coordinate_systems_octave_example.py
# Created by:       wiki.gis/MiguelRBF
#---------------

# Octave v6.3.0 documentation:
# https://octave.org/doc/v6.3.0/

clear all
close all
clc

# Define the ellipsoid model
model='wgs84';
# Get the ellipsoid parameters
ell = ellipsoidModel(model);

x=4325481.828902193;
y=565424.2388267403;
z=4638228.339585699;

# Variable to set degres as input/output
deg=1;

[lat, long, alt] = ecef2lla(x,y,z,ell,deg);

fprintf('The latitude is: %f\n',lat);
fprintf('The longitude is: %f\n',long);
fprintf('The altitude is: %f\n',alt);

%% reference point
refLat = 39*pi/180;
refLong = -132*pi/180;
refH = 0;
 
%% Points of interest
lat = [39.5*pi/180; 39.5*pi/180;39.5*pi/180];
long = [-132*pi/180;-131.5*pi/180;-131.5*pi/180];
h = [0;0;1000];
 
disp('lat long height')
for i = 1:length(lat)
    disp([num2str(lat(i)*180/pi),' ', num2str(long(i)*180/pi), ' ',num2str(h(i))])
end
% lat = [39.5*pi/180];
% long = [-132*pi/180];
% h = [0];
 
%% convering lla to enu
[Xr,Yr,Zr] = lla2ecef(refLat,refLong,refHell,ell,deg);
[X,Y,Z] = lla2ecef(lat,long,hell,ell,deg);
disp('X Y Z')
 
for i = 1:length(X)
    disp([num2str(X(i)),' ', num2str(Y(i)), ' ',num2str(Z(i))])
end
 
[e,n,u] = ecef2enu_ecefRef(Xr, Yr, Zr, X, Y, Z,ell,deg);
disp('e n u')
for i = 1:length(e)
   disp([num2str(e(i)),' ', num2str(n(i)), ' ',num2str(u(i))])
end
 
%% Converting enu to lla
[X, Y, Z] = enu2ecef_llaRef(refLat, refLong, refH, e, n, u, ell,deg);
disp('X Y Z')
for i = 1:length(X)
    disp([num2str(X(i)),' ', num2str(Y(i)), ' ',num2str(Z(i))])
end
 
[phi, lambda, h] = ecef2lla(X,Y,Z,ell,deg);
disp('\phi \lambda h')
for i = 1:length(X)
    disp([num2str(phi(i)*180/pi),' ', num2str(lambda(i)*180/pi), ' ',num2str(h(i))])
end