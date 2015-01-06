function [R, t] = point_register(X, Y)
% SDB: modified to not return FRE
%function [R, t, FRE] = point_register(X, Y)
% This function performs point-based rigid body registration with equal
% weighting for all fiducials. It returns a rotation matrix, translation
% vector and the FRE.
if nargin < 2
  error('At least two input arguments are required.');
end

[Ncoords Npoints] = size(X);
[Ncoords_Y Npoints_Y] = size(Y);

if Ncoords ~= 3 | Ncoords_Y ~= 3
  error('Each argument must have exactly three rows.')
elseif (Ncoords ~= Ncoords_Y) | (Npoints ~= Npoints_Y)
  error('X and Y must have the same number of columns.');
elseif Npoints < 3
  error('X and Y must each have 3 or more columns.');
end

Xbar = mean(X,2); % X centroid
Ybar = mean(Y,2); % Y centroid
Xtilde = X-repmat(Xbar,1,Npoints); % X relative to centroid
Ytilde = Y-repmat(Ybar,1,Npoints); % Y relative to centroid
H = Xtilde*Ytilde'; % cross covariance matrix
[U S V] = svd(H); % U*S*V' = H
R = V*diag([1, 1, det(V*U)])*U';
t = Ybar - R*Xbar;
% SDB: leave this out for accurate run-time
% FREvect = R*X + repmat(t,1,Npoints) - Y;
% FRE = sqrt(mean(sum(FREvect.^2,1)));
end