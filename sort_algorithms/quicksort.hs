qs :: [Int] -> [Int]
qs [] = []
qs (x:xs) = filter (<x) xs ++ [x] ++ filter (>x) xs

main = print $ qs [1, 8, 5, 1, 3, 7, 9]
