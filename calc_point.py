import math

EPSILON = 0.01
SCALE = 851.0 / 55.45


def solve_deg2(a, b, c):
    delta = b * b - 4 * a * c
    fd = math.fabs(delta)

    if fd < EPSILON:
        x1 = -b / (2 * a)
        return x1,
    elif delta < 0:
        return None
    else:
        x1 = (-b + math.sqrt(delta)) / (2 * a)
        x2 = -b / a - x1
        return x1, x2


class MyDistance:
    def __init__(self, distance, c, mid):
        self.d = distance
        self.c = c
        self.mid = mid

    def __repr__(self):
        return '(%f, %s)' % (self.d, self.c)


def fine_tuning(r1, r2, d):
    edges = [MyDistance(r1, 1.5, 0), MyDistance(r2, 1.5, 1), MyDistance(d, 0, 2)]

    sorted(edges, key=lambda e: e.d)

    delta = edges[0].d + edges[1].d - edges[2].d
    if delta < 0:
        delta = math.fabs(delta)
        denom = edges[0].c + edges[1].c + edges[2].c
        edges[0].d += (edges[0].c / denom) * delta
        edges[1].d += (edges[1].c / denom) * delta
        edges[2].d -= (edges[2].c / denom) * delta

    sorted(edges, key=lambda e: e.mid)

    return edges[0].d, edges[1].d, edges[2].d


def calc_cord_from_distance(p1, r1, p2, r2):
    x1, y1 = p1
    x2, y2 = p2

    print(r1, r2)

    r1 *= SCALE
    r2 *= SCALE

    d12 = math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

    r1, r2, d12 = fine_tuning(r1, r2, d12)
    print(r1/SCALE, r2/SCALE)

    if math.fabs(y1 - y2) < EPSILON:
        if math.fabs(x1 - x2) < EPSILON:
            return None
        else:
            x = (x1 * x1 - x2 * x2 - (r1 * r1 - r2 * r2)) / (2 * (x1 - x2))

            tmp = r1 * r1 - (x - x1) * (x - x1)
            ft = math.fabs(tmp)

            if ft < EPSILON:
                # ~ 0
                s1 = (x, y1)
                return s1
            elif tmp < 0:
                return None
            else:
                st = math.sqrt(tmp)
                s1 = (x, st + y1)
                s2 = (x, -st + y1)
                return s1, s2

    a = (x2 - x1) / (y1 - y2)
    b = (x1 * x1 - x2 * x2 + y1 * y1 - y2 * y2 - (r1 * r1 - r2 * r2)) / (2 * (y1 - y2))
    c = b - y1

    ret = solve_deg2(a * a + 1, 2 * (a * c - x1), x1 * x1 + c * c - r1 * r1)

    if ret is None:
        return None
    elif len(ret) == 1:
        s1 = (ret[0], a * ret[0] + b)
        return s1,
    else:
        s1 = (ret[0], a * ret[0] + b)
        s2 = (ret[1], a * ret[1] + b)
        return s1, s2


p1 = (23, 438)
p2 = (874, 438)

result = calc_cord_from_distance(p1, 17.05, p2, 49.07)

print(result)
