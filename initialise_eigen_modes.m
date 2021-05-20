phi = @(x,n) (10/pi)^(0.25)*1/sqrt(2^n*factorial(n))*exp(-5*x.*x)*hermiteH(n,sqrt(10)*x);
phivalues1 = zeros(1,length(points));
phivalues2 = zeros(1,length(points));
phivalues3 = zeros(1,length(points));

for i = 1:length(points)
    phivalues1(i) = phi(points(i),0);
    phivalues2(i) = phi(points(i),1);
    phivalues3(i) = phi(points(i),2);
end