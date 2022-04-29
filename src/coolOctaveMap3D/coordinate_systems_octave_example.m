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

disp('xyz coordinates')
x=4325481.828902193
y=565424.2388267403
z=4638228.339585699

# Variable to set degres as input/output
deg=1;

disp('Converting xyz to lla')
[lat, long, alt] = ecef2lla(x,y,z,ell,deg);

fprintf('The latitude is: %f\n',lat);
fprintf('The longitude is: %f\n',long);
fprintf('The altitude is: %f\n\n',alt);

%% reference lla point
refLat = 39.0*pi()/180.0
refLong = -132.0*pi()/180.0
refH = 0.0
 
# Points of interest
#lat = [39.5*pi/180; 39.5*pi/180;39.5*pi/180];
#long = [-132*pi/180;-131.5*pi/180;-131.5*pi/180];
#h = [0;0;1000];
 
#disp('lat long height')
#for i = 1:length(lat)
#    disp([num2str(lat(i)*180/pi),' ', num2str(long(i)*180/pi), ' ',num2str(h(i))])
#end

%% lla point
disp('lla coordinates')
lat = [39.5*pi/180]
long = [-132*pi/180]
h = [0]
 
%% Converting lla to enu
disp('Converting lla to enu')
[Xr,Yr,Zr] = lla2ecef(refLat,refLong,refH,ell,deg);
[X,Y,Z] = lla2ecef(lat,long,h,ell,deg);

fprintf('The x coordinate is: %f\n',X);
fprintf('The y coordinate is: %f\n',Y);
fprintf('The z coordinate is: %f\n',Z);
 
#for i = 1:length(X)
#    disp([num2str(X(i)),' ', num2str(Y(i)), ' ',num2str(Z(i))])
#end
 
[e,n,u] = ecef2enu_ecefRef(Xr, Yr, Zr, X, Y, Z,ell,deg);
fprintf('The e coordinate is: %f\n',e);
fprintf('The n coordinate is: %f\n',n);
fprintf('The u coordinate is: %f\n\n',u);

#for i = 1:length(e)
#   disp([num2str(e(i)),' ', num2str(n(i)), ' ',num2str(u(i))])
#end
 
disp('Converting enu to lla')
%% Converting enu to lla
[X, Y, Z] = enu2ecef_llaRef(refLat, refLong, refH, e, n, u, ell,deg);

fprintf('The x coordinate is: %f\n',X);
fprintf('The y coordinate is: %f\n',Y);
fprintf('The z coordinate is: %f\n\n',Z);

#disp('X Y Z')
#for i = 1:length(X)
#    disp([num2str(X(i)),' ', num2str(Y(i)), ' ',num2str(Z(i))])
#end

disp('Converting enu to lla')
[phi, lambda, h] = ecef2lla(X,Y,Z,ell,deg);
fprintf('The phi coordinate is: %f\n',phi);
fprintf('The lambda coordinate is: %f\n',lambda);
fprintf('The h coordinate is: %f\n',h)

#disp('\phi \lambda h')
#for i = 1:length(X)
#    disp([num2str(phi(i)*180/pi),' ', num2str(lambda(i)*180/pi), ' ',num2str(h(i))])
#end